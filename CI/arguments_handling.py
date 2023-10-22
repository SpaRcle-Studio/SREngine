import sys 

ciValues = ["#SR_CI_NONE", "#SR_CI_RELEASE", "#SR_CI_DEBUG", "#SR_CI_ALL"]
ciArguments = []
            
def main():
    for value in ciValues:
        for arg in sys.argv:
            if arg ==  value:
                ciArguments.append(value)
            
    for argument in ciArguments:
        argument[1:]
        print(f"{argument}=true")
        ciValues.remove(argument)
        
    for value in ciValues:
        value[1:]
        print(f"{argument}=false")
    
if __name__ == "__main__":
    main()