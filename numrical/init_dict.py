#!/usr/bin/env python
#-*- coding:utf-8 -*-

def init_dict(fp):
    cal_dir = fp+'/calendar_dates.txt'
    trips_dir = fp + '/trips.txt'
    stops_dir = fp + '/stops.txt'
    stop_times_dir = fp + '/stop_times.txt'
    routes_dir=fp+'/routes.txt'

    cal_dict = {}
    trips_dict = {}
    stops_dict = {}
    stop_times_dict = {}
    routes_dict={}
    routes_trip_dict={}
    route_type_dict={}
    
    r=open(routes_dir,'r')
    for line in r:
        if 'route_id' in line:
            continue
        k=line.split(',')
        routes_dict[k[0].strip()]=k[2].strip()
        route_type_dict[k[0].strip()]=k[-3].strip()
    r.close()
    r = open(cal_dir,'r')
    for line in r:
        if 'service_id' in line:
            continue
        k = line.split(',')
        if not cal_dict.has_key(k[1].strip()):
            cal_dict[k[1].strip()] = [k[0].strip()]
        else:
            cal_dict[k[1].strip()].append(k[0].strip())
    r.close()
    r = open(trips_dir,'r')
    for line in r:
        if 'service_id' in line:
            continue
        k = line.split(',')
        if not trips_dict.has_key(k[1].strip()):
            trips_dict[k[1].strip()] = [k[2].strip()]
        else:
            trips_dict[k[1].strip()].append(k[2].strip())
        if not routes_trip_dict.has_key(k[0].strip()):
            routes_trip_dict[k[0].strip()]=[k[2].strip()]
        else:
            routes_trip_dict[k[0].strip()].append(k[2].strip())
    r.close()
    r = open(stops_dir,'r')
    for line in r:
        if 'stop_id' in line:
            continue
        k = line.split(',')
        stops_dict[line.split(',')[0].strip()] = [ k[1],k[3],k[2] ]
    r.close()

    r = open(stop_times_dir,'r')
    for line in r:
        if 'trip_id' in line:
            continue
        k = line.split(',')
        if not stop_times_dict.has_key(k[0].strip()):
            stop_times_dict[k[0]] = [k[1].strip()]
        else:
            stop_times_dict[k[0]].append(k[1].strip())

    r.close()

    return cal_dict, trips_dict, stops_dict, stop_times_dict,routes_dict,routes_trip_dict,route_type_dict





