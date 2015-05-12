__author__='BingzheWu'
import urllib
import lxml
import re
import sys
reload(sys)
def getInfo(r,w):
	num=1
	for person in r:
		person=','.join(person.split())
		print person
		personName=person.split(',')[0]
		personId=person.split(',')[1]
		if divmod(num,5)[1]==0:
			w.write(personName+'('+personId+')'+'\n')
		else:
			w.write(personName+'('+personId+')'+'   ')
		num=num+1
	print num
if __name__=='__main__':
	fileName=sys.argv[1]
	outFile=sys.argv[2]
	r=open(fileName,'r')
	w=open(outFile,'w')
	getInfo(r,w)


		
	

