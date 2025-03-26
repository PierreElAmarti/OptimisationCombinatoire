import os
import subprocess
from pathlib import Path
#os.system("touch output.csv")
root = Path("./convert/")
buildPath="./Knapsack/build"
#os.system("buildPath+"/src/Heur convert/kplib-master/00Uncorrelated/n00050/R01000/s000.kp ")
#test=subprocess.check_output("buildPath+"/src/BB "+"convert/kplib-master/00Uncorrelated/n00050/R01000/s000.kp ", shell=True)
#print(str(test).replace('\\n','\n'))
baseFileName="resBB"
i=0

#creation du nouveau fichier de res (le fichier 'nb' sert à mémoriser le chiffre courant)
nb=subprocess.check_output("ls resultats/ | grep ^[0-9]$",shell=True,errors=False)
nb_nouv=(int(nb[:1])+1)
nb=int(nb[:1])
subprocess.check_output("touch resultats/"+baseFileName+""+str(nb_nouv)+".csv",shell=True,errors=False)
subprocess.check_output("mv resultats/"+str(nb)+" resultats/"+str(nb_nouv)+"",shell=True,errors=False)
var=subprocess.check_output("echo \"file name;TYPE;cost;upper bound;rounded upper bound;gap;time\" > resultats/"+baseFileName+""+str(nb_nouv)+".csv",shell=True,errors=False)

for path in root.glob("**/*"):
    if(str(path)[len(str(path))-2:]=="kp" or str(path)[len(str(path))-2:]=="in" ):
        try:
            test=subprocess.check_output(buildPath+"/BB ./"+str(path)+" resultats/"+baseFileName+""+str(nb_nouv)+".csv", shell=True,errors=False)
            #print("./"+str(path))
            i+=1
        except:
            pass
        #print(test)
    else:
        pass
    if(i==1): #NB max d'instances à tester
        break

    print("fichier de sortie : resultats/"+baseFileName+""+str(nb_nouv)+".csv")

