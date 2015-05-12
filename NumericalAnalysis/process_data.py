import re

def process_data(fn,w):
    r=open(fn,'r')
    
    for line in r:
        #print line
        i1=''
        line=line.split(']')
        for i in line[:-1]:
            if '~' in i:
                i1+=i+']'
            else:
                i1+=i[:-5]+'.'+i[-4:-2]+'~'+i[-7:-5]+'.'+i[-4:-2]+':0'+']'
        w.write(i1+'\n')
        #print i1
    r.close()
if __name__=='__main__':
    w=open('res_data1','w')
    process_data('res_data',w)
    w.close()

