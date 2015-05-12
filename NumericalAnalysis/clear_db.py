#!/usr/bin/env python
#-*- coding:utf-8 -*- 
import re
from station_db import QueryBySQL as QUERY

def clear_db():
	sql_str = 'delete from gtfs_agency'
	QUERY(sql_str)
    sql_str = 'delete from gtfs_calendar'
	QUERY(sql_str)
	sql_str = 'delete from gtfs_stops'
	QUERY(sql_str)
	sql_str = 'delete from gtfs_transfers'
	QUERY(sql_str)
	sql_str = 'delete from gtfs_calendar_dates'
	QUERY(sql_str)
	sql_str = 'delete from gtfs_routes'
	QUERY(sql_str)
	sql_str = 'delete from gtfs_stop_times'
	QUERY(sql_str)
	sql_str = 'delete from gtfs_trips'
	QUERY(sql_str)


	return 

if __name__ == '__main__':
	clear_db()

