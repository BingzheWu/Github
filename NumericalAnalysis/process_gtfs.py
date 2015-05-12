            #!/usr/bin/env python
#-*- coding:utf-8 -*-
import re
import os
import time
from process_time import process_time
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
from init_dict import init_dict
def count_time(a,b):
    #print int(a.split(':')[1]
    t1 = int(a.split(':')[0])*60+int(a.split(':')[1])
    t2 = int(b.split(':')[0])*60+int(b.split(':')[1])
    return str(abs(t1-t2))
def process_stop_times(line_name,w,fn, cal_dict, trips_dict, stops_dict,stop_times_dict,task_date,dayOfWeek):
    r = open(fn,'r')
    pre = 0
    key_dic = {} ; start_time = {} ; task_trip_list = []
    temp_sign = '' ; pre_trip_id = ''
    
    list_1 = cal_dict[task_date]
    for i in list_1:
        if trips_dict.get(i):
            task_trip_list += trips_dict[i]
        else:
            continue
    for line in r:
        if 'trip_id' in line: continue
        if not stop_times_dict.has_key(line.split(',')[0]):
            continue
        if line.split(',')[0].strip() == pre:
            temp_sign += '#'+line.split(',')[3].strip()
        else:
            if pre != 0 and not key_dic.has_key(temp_sign) :
                key_dic[temp_sign] = [pre]
            elif key_dic.get(temp_sign):
                key_dic[temp_sign].append(pre)

            pre = line.split(',')[0]
            temp_sign = line.split(',')[3].strip()
            start_time[pre]=line.split(',')[1]
    if not key_dic.has_key(temp_sign):
        key_dic[temp_sign] = [pre]
    else:
        key_dic[temp_sign].append(pre)
    
    res_list = []
    for key,value in key_dic.items():
        tt = []
        runningtime_sign = 0 
        runningtime_list = []
        triptrip_id = ''
        for i in value:
            if i in task_trip_list:
                if not runningtime_sign:
                    runningtime_list = stop_times_dict[i]
                    triptrip_id = '###'+i+'###'
                    runningtime_sign = 1
                tt.append(start_time[i][:-3])

        runningtime_list = '&'.join(runningtime_list)
        runningtime_list = '___'+runningtime_list+'___'
        tt.sort()

        res_list.append('{'+key+'}'+triptrip_id+runningtime_list+'['+dayOfWeek+':'+'&'.join(tt)+']')

    line_name =line_name
    time_dict = {}
    cnt = 0
    for i in res_list:
        cnt += 1
        str1 = re.findall('\[(.*$)',i)[0][:-1]
        print str1
        print'---------------------'
#        print str1
        str2 = re.findall('\{(.*)\}',i)[0]
        str3 = re.findall('___(.*)___',i)[0]
        

        station_res_list = []
        cntcnt = 0
        if str3!='':
            station_list = str2.split('#')
            running_time_list = str3.split('&')
        else:
            continue
        running_time_res_list = []
        init_time = running_time_list[0] 
        if len(running_time_list)==len(station_list) and init_time!='':
            for j in running_time_list:
                if j!='':
                
                    running_time_res_list.append( count_time(j,init_time) )
        else:
           continue 
        count_cnt = -1
        for j in station_list:
            count_cnt += 1
            cntcnt += 1
            if len(running_time_res_list)!=0:
                if count_cnt <len(running_time_res_list):
                    station_j = stops_dict[j][0]+'&'+stops_dict[j][1]+','+stops_dict[j][2]+'&'+str(cntcnt)+'&'+running_time_res_list[count_cnt]
                else:
                    continue
                station_res_list.append(station_j)
            else:
                continue
        station_res_list='&&&'.join(station_res_list)

#        w.write(line_name+'_'+str(cnt)+'###NULL###NULL###'+station_res_list+'###'+str2+ process_time(str1)+'\n')
        w.write(line_name+'_'+str(cnt)+'###NULL###NULL###NULL###'+station_res_list+'###'+':'+ process_time(str1)+'\n')

    return  

def init_data(f):
    x = time.time()
    #print 0
    #print '-------------------------'
    cal_dict,trips_dict,stops_dict,stop_times_dict,routes_dict,routes_trip_dict,route_type_dict=init_dict(f)
    DATA_dict={}
   # print routes_dict
    for key in routes_dict:
        info_list=[]
        trips_temp_dict,stop_times_temp_dict={},{}
        if routes_trip_dict.has_key(key):
            trip_temp=routes_trip_dict[key]#找到key对应的trip_list
        else:
            continue
        for trip in trip_temp:
            if stop_times_dict.has_key(trip):
                stop_times_temp_dict[trip]=stop_times_dict[trip]
            else:
                continue
            for j in trips_dict:
                if trip in set(trips_dict[j]):
                    trips_temp_dict[j]=trips_dict[j]
                else:
                    continue
        info_list+=[cal_dict]+[trips_temp_dict]+[stops_dict]+[stop_times_temp_dict]
        DATA_dict[key]=info_list
        #print info_list
   # print '============================================='
    print time.time() - x, 'init func'
    return DATA_dict,routes_dict,route_type_dict

            
        #DATA_dict[key]=routes_trip_dict[key]

        

def process_data(w,fn):
    filelist = os.listdir(fn)
    temp_list = []
    for i in filelist:
        temp_list.append(fn+i)
    filelist = temp_list
    pre = 0
    for i in filelist:

        print i
        week = ['MON','TUE','WED','THU','FRI','SAT','SUN']
        DATA_dict,routes_dict,route_type_dict=init_data(i)
        for route in DATA_dict:
            line_name =route_type_dict[route].strip()+'_line'+routes_dict[route].strip()
            cal_dict,trips_dict,stops_dict,stop_times_dict=DATA_dict[route][0],DATA_dict[route][1],DATA_dict[route][2],DATA_dict[route][3]
            cnt=-1
            for j in range(1,8):
                cnt += 1
                dayOfWeek = week[cnt]
                year = '2015';month = '04';#修改
                if j<10:

                    day=year+month+'0'+str(j)
                else:

                    day = year+month+str(j)
                process_stop_times(line_name,w,i+'/stop_times.txt',cal_dict,trips_dict,stops_dict,stop_times_dict,day,dayOfWeek)
            
    return

def res_process(fn,out):
    r = open(fn,'r')
    res_dict = {}
    for line in r:
        kk = line[:line.find('###')]
        vv = line[line.find(':')+1:]
        if res_dict.get(kk):
            res_dict[kk] += vv.strip()
        else:
#            res_dict[kk] = vv.strip()
            res_dict[kk] = line[line.find('###'):].strip()
    w = open(out,'w')
    for key,value in res_dict.items():
        ttt = key+value+'\n'
        ttt = ttt.replace('###:','###',10)
#        w.write(key+value+'\n')
        w.write(ttt)
    w.close()

if __name__ == '__main__':
    print 'begin'
    x = time.time()
    w = open('temp_write1','w')
    process_data(w,'./DATA/')
    w.close()
    res_process('temp_write1','res_data')
    print time.time() -x , 'all func'
