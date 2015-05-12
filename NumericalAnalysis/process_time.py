#!/usr/bin/env python
#-*- coding:utf-8 -*-
import re
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

def get_interval_time(begin,end):
	return int(end.split(':')[0])*60 + int(end.split(':')[1]) - \
			int(begin.split(':')[0])*60 - int(begin.split(':')[1])

def process_time(content):
	#print 'real'
	#print content
	real = content
	content = content[4:].strip()
	time_list = content.split('&')
	#print time_list
	num = len(time_list)
	if num == 1:
		return '['+real[0:4]+time_list[0]+':0]'
	temp_list = []
	temp_list.append(time_list[0])
	temp_list.append(time_list[1])
	preinterval = abs(get_interval_time(time_list[0],time_list[1]))
	for i in range(2,num):
		if abs(abs(get_interval_time(time_list[i-1], time_list[i])) - preinterval) >3:
			if i+1 == num:
				temp_list.append(time_list[i])
			else:
				preinterval = abs(get_interval_time(time_list[i+1],time_list[i]))
				temp_list.append('#'+time_list[i])
		else:
			temp_list.append(time_list[i])
	temp_list = '&'.join(temp_list)
	interval_list = temp_list.split('&#')
	#print len(interval_list)
	#print interval_list[0]
	res_list = []
	for times in interval_list:
		list1 = times.split('&')
		sum = 0
		num1 = len(list1)
		for i in range(1,num1):
			sum += abs(get_interval_time(list1[i],list1[i-1]))
		if num1 == 1:
			ave = sum
		else:
			ave = sum/(num1-1)
		temp_str = list1[0].replace(':','.',10).strip() + '~' + list1[-1].replace(':','.',10).strip() + ':' + str(ave)
		res_list.append('['+real[0:4]+temp_str+']')
	t = ''.join(res_list)
	res_list = t
	return res_list

if __name__ == '__main__':
	r = open('test1','r')
	for line in r:
		content = line.split('###')[-1].strip()
		print process_time(content)
		


