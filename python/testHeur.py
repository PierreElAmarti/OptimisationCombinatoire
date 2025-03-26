import os
import subprocess
from pathlib import Path
#os.system("touch output.csv")
root = Path("./instances/")
buildPath="./Knapsack/build"
#os.system("buildPath+"/src/Heur convert/kplib-master/00Uncorrelated/n00050/R01000/s000.kp ")
#test=subprocess.check_output("buildPath+"/src/BB "+"convert/kplib-master/00Uncorrelated/n00050/R01000/s000.kp ", shell=True)
#print(str(test).replace('\\n','\n'))
baseFileName="resHeur"


numFile=Path("./resultats/numero.conf")
if not(os.path.isfile(numFile)):
    print("creation fichier de conf")
    num="1"
else:
    print("fichier de configuration trouve")
    num=""
fich=open(str(numFile),"a")
fich.write(num)
fich.close()
fich=open(str(numFile),"r")
nb=fich.read(1)
fich.close()
fich=open(str(numFile),"w")
fich.write(str(int(nb)+1))
fich.close()
#creation du nouveau fichier de res (le fichier 'nb' sert à mémoriser le chiffre courant)
#nb=subprocess.check_output("ls resultats/ | grep ^[0-9]$",shell=True,errors=False)

subprocess.check_output("touch resultats/"+baseFileName+""+str(nb)+".csv",shell=True,errors=False)
var=subprocess.check_output("echo \"file name;TYPE;cost;upper bound;rounded upper bound;gap;time\" > resultats/"+baseFileName+""+str(nb)+".csv",shell=True,errors=False)

i=0
for path in sorted(root.glob("**/*"),reverse=True):
    if(str(path)[len(str(path))-2:]=="kp" or str(path)[len(str(path))-2:]=="in" ):
        try:
            test=subprocess.check_output(buildPath+"/Heur ./"+str(path)+" resultats/"+baseFileName+""+str(nb)+".csv", shell=True,errors=False)
            #print("./"+str(path))
            i+=1
        except:
            pass
        #print(test)
    else:
        pass
    if(i==1): #NB max d'instances à tester
        break

print("fichier de sortie : resultats/"+baseFileName+""+str(nb)+".csv")

