#coding:utf-8
#导入模块#
import urllib
import urllib2
import mechanize
import cookielib
import random
import json
import sys
import time
from logger import logger

user_agent_list = ['Mozilla/5.0 (Windows NT 6.1; WOW64; rv:29.0) Gecko/20100101 Firefox/29.0', 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.116 Safari/537.36']


class MechanizeCrawler(object):
    '''
    A basic crawl tool using mechanize.
    automatic configuration, but only support get request, now.
    '''

    # init, referer, headers and proxy can be set here
    def __init__(self, referer = '', headers = {}, p = ''):
        self.debug = False
        self.br = mechanize.Browser()
        
        self.cj = cookielib.LWPCookieJar()
        self.br.set_cookiejar(self.cj)
        
        self.br.set_handle_equiv(True)
        self.br.set_handle_gzip(True)
        self.br.set_handle_redirect(True)
        self.br.set_handle_referer(True)
        self.br.set_handle_robots(False)

        self.br.set_handle_refresh(mechanize._http.HTTPRefreshProcessor(), max_time=1)
        self.br.addheaders = [('User-agent', 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:29.0) Gecko/20100101 Firefox/29.0')]
        
        # add referer
        if len(referer) > 0 and referer != 'None' and referer != None and referer != 'NULL':
            self.br.addheaders += [('Referer', referer), ]

        # add headers, referer can also be put here
        for key in headers.keys():
            self.br.addheaders += [(key, headers[key]), ]

        # set proxy
        if len(p) > 0 and p != 'None' and p != None and p != 'NULL':
            self.br.set_proxies({'http': p})

    # set debug
    def set_debug(self, flag = False):
        self.debug = flag
        if self.debug:
            self.br.set_debug_http(True)
            self.br.set_debug_redirects(True)
            self.br.set_debug_responses(True)
        elif not self.debug:
            self.br.set_debug_http(False)
            self.br.set_debug_redirects(False)
            self.br.set_debug_responses(False)

    # get
    # paras_type: when using post, 0, urllib.urlencode; 1, json.dumps; 2, unchanged
    def req(self, method, url_base, paras = {}, paras_type = 1, html_flag = False, time_out = 60):
        if method.lower() == 'get':
            url = url_base + urllib.urlencode(paras)
        elif method.lower() == 'post':
            url = url_base
        else:
            logger.error('req, wrong method(post or get)')
            sys.exit(-1)

        html = ''
        try:
            #print url
            if method.lower() == 'get':
                resp = self.br.open(url, timeout=time_out)
            else:
                if paras_type == 1:
                    paras = json.dumps(paras)
                elif paras_type == 0:
                    paras = urllib.urlencode(paras)
                elif paras_type == 2:
                    pass
                else:
                    logger.error('req, wrong paras type( 0 or 1)')
                resp = self.br.open(url, paras, timeout=time_out)


            if html_flag:
                html = resp.get_data()
        
        except Exception, e:
            if self.debug:
                logger.error(str(e))

        return html

    def get_url(self, method, url_base, paras = {}, paras_type = 1, time_out = 60):

        if method.lower() == 'get':
            url = url_base + urllib.urlencode(paras)
        elif method.lower() == 'post':
            url = url_base
        else:
            logger.error('req, wrong method(post or get)')
            sys.exit(-1)

        getURL = ''
        try:
            if method.lower() == 'get':
                resp = self.br.open(url, timeout=time_out)
            else:
                if paras_type == 1:
                    paras = json.dumps(paras)
                elif paras_type == 0:
                    paras = urllib.urlencode(paras)
                elif paras_type == 2:
                    pass
                else:
                    logger.error('req, wrong paras type( 0 or 1)')
                resp = self.br.open(url, paras, timeout=time_out)
            
            getURL = self.br.geturl()

        except Exception, e:
            if self.debug:
                logger.error('getURL Error: ' + str(e))

        return getURL
        
        
    def get_res(self, url):
        image = ''
        try:
            vcode_data = self.br.open_novisit(url)
            image = vcode_data.read()
        except Exception, e:
            if self.debug:
                logger.error('get resource failed')

        return image

    # set referer individually
    def add_referer(self, url):
        d = dict(self.br.addheaders)
        d['Referer'] = url
        self.br.addheaders = d.items()

    # set header individually
    def add_header(self, headers = {}):
        d = dict(self.br.addheaders)
        for key in headers:
            d[key] = headers[key]
            self.br.addheaders = d.items()

    # set proxy individually
    def set_proxy(self, p):
        self.br.set_proxies({'http': p})

    def get_cookie_handle(self):
        cookie_handle_pos = -1
        for i in xrange(0, len(self.br.handlers)):
            #logger.info(mc.br.handlers[i])
            if str(self.br.handlers[i]).find('Cookie') != -1:
                cookie_handle_pos = i
        if cookie_handle_pos != -1:
            return self.br.handlers[cookie_handle_pos]
        else:
            return None



if __name__ == '__main__':

    md = MechanizeCrawler()
    #mc.set_proxy('124.230.118.20:8088')
    md.set_debug(flag = True)
    md.add_header(headers={'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8', 'Accept-Language':'zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3', 'Connection':'keep-alive'})
    
    '''
    #
    url1 = 'http://www.feiquanqiu.com/ticketsearch?q=search&type=oneway&departureAirport=BJS&destinationAirport=PAR&departureDate=08%2F18%2F2014&adults=1&children=0&cabin=E&btn-search=%E6%9F%A5%E8%AF%A2'
    url2 = 'http://www.feiquanqiu.com/ticketsearch?departureAirport=BJS&destinationAirport=PAR&departureDate=08/18/2014&returnFromAirport=&returnToAirport=&returnDate=&type=oneway&adults=1&children=0&cabin=E'
    mc.req('get', url1)
    import time
    n = 0
    html = ''
    while len(html) < 1000 and n < 5:
        print n
        n += 1
        html = mc.req('get', url2, html_flag = True)
        time.sleep(5)
    print html
    '''
    
    # venere
    print time.time()
    url1 = 'http://www.venere.com/hotels/paris/hotel-regina-montmartre/?sd=18&sm=8&sy=2014&ed=20&em=8&ey=2014&rgval=2||-1'
    md.req('get', url1)
    print time.time()

    cookie_handle = md.get_cookie_handle()
    if type(cookie_handle).__name__ != 'instance':
        sys.exit(-1)
    # if want to know the detail structure of cookie
    #print cookie_handle.cookiejar._cookies
    _abs = cookie_handle.cookiejar._cookies['.venere.com']['/']['_abs'].value

    print _abs

    time.sleep(10)
    web_id = cookie_handle.cookiejar._cookies['.venere.com']['/']['WEB_ID'].value
    

    url2 = 'http://services.venere.com/search/01/services_mashup/mashupper.json'
    datas = {"mashup":"services_script_mashupper","param":{"context":"HDP_AVAIL","version":"5.1.0","input":{"user_agent":"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.153 Safari/537.36","property_id":474620,"avail":{"checkin":"2014-08-18","checkout":"2014-08-20","rgval":"2||-1"},"user_prefs":{"lg":"en","country_code":"CN","currency_code":"CNY"},"ref":{}},"session":{"abs":_abs,"webid":web_id}}}
    html =  mc.req('post', url2, datas, html_flag = True)
    print html


    '''
    # 东方航空
    print '东方航空'
    url1 = 'http://easternmiles.ceair.com/flight/sha-cdg-140807_CNY.html'
    url2 = 'http://easternmiles.ceair.com/booking/flight-search!doFlightSearch.shtml?rand=0.9618372581669741'
    mc.req('get', url2)
    import json
    datas = {"segmentList":[{"deptCdTxt":"上海","deptCd":"SHA#","deptNation":"CN","deptRegion":"CN","deptCityCode":"SHA","arrCd":"CDG#","arrCdTxt":"巴黎","arrNation":"FR","arrRegion":"EU","arrCityCode":"PAR","deptDt":"2014-08-07"}],"tripType":"OW","adtCount":1,"chdCount":0,"infCount":0,"currency":"CNY","sortType":"t"}
    datas = 'searchCond='+json.dumps(datas)
    html = mc.req('post', url2, datas, html_flag = True)
    print html
    print
    print

    print '**************************************************************************************'
    print '**************************************************************************************'

    print
    print
    '''

    '''
    import time
    r = str(int(100 * time.time()))
    # jijitong
    url1 = 'http://www.jijitong.com/'
    url2 = 'http://www.jijitong.com/beijing-bali.html?20140730'
    url3 = 'http://www.jijitong.com/handle/FlightHandler.ashx?t0.18522175865624846&fromCity=%E5%8C%97%E4%BA%AC&toCity=%E5%B7%B4%E9%BB%8E&fromDate=2014-07-30&toDate=&adtCount=1&chdCount=0&class=Y&stops=2&currency=CNY&vendors=&vcode=&_=' + r
    mc.req('get', url1)
    mc.req('get', url2)
    html = mc.req('get', url3, html_flag = True)
    print html
    '''

    
