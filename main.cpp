#include <stdint.h>
#include <stdio.h>
#include <vector>
#define REG(a) (a<0x8000?a:mem[a])
using namespace std;

int main(){
	uint16_t mem[0x8008];
	vector<uint16_t> myStack;
	unsigned int itr = 0;
	uint8_t buf[2]; 
	FILE* pFile = fopen("challenge.bin", "r");

	for(int i = 0; i < 0x8000; ++i){
		if(fread(buf,1,2,pFile) != 2) break;
		mem[i] = buf[0]|(buf[1]<<8);
	}
	fclose(pFile);

	while(1){
		switch(mem[itr]){
			case 0:
				return 0;
			case 1:
				mem[mem[itr+1]] = REG(mem[itr+2]);
				itr += 3;
				break;
			case 2:
				myStack.push_back(REG(mem[itr+1]));
				itr += 2;
				break;
			case 3:
				if(myStack.empty())
					perror("Error: Failed to pop stack");
				else{
					mem[mem[itr+1]] = myStack.back();
					myStack.pop_back();
				}
				itr += 2;
				break;
			case 4:
				if(REG(mem[itr+2]) == REG(mem[itr+3]))
					mem[mem[itr+1]] = 1;
				else
					mem[mem[itr+1]] = 0;
				itr += 4;
				break;
			case 5:
				if(REG(mem[itr+2]) > REG(mem[itr+3]))
					mem[mem[itr+1]] = 1;
				else
					mem[mem[itr+1]] = 0;
				itr += 4;
				break;
			case 6:
				itr = REG(mem[itr+1]);
				break;
			case 7:
				if(REG(mem[itr+1]) != 0)
					itr = REG(mem[itr+2]);
				else
					itr += 3;
				break;
			case 8:
				if(REG(mem[itr+1]) == 0)
					itr = REG(mem[itr+2]);
				else
					itr += 3;
				break;
			case 9:
				mem[mem[itr+1]] = (REG(mem[itr+2]) + REG(mem[itr+3])) % 0x8000;
				itr += 4;
				break;
			case 10:
				mem[mem[itr+1]] = (REG(mem[itr+2]) * REG(mem[itr+3])) % 0x8000;
				itr += 4;
				break;
			case 11:
				mem[mem[itr+1]] = REG(mem[itr+2]) % REG(mem[itr+3]);
				itr += 4;
				break;
			case 12:
				mem[mem[itr+1]] = REG(mem[itr+2]) & REG(mem[itr+3]);
				itr += 4;
				break;
			case 13:
				mem[mem[itr+1]] = REG(mem[itr+2]) | REG(mem[itr+3]);
				itr += 4;
				break;
			case 14:
				mem[mem[itr+1]] = ~(REG(mem[itr+2]))&0x7fff; 
				itr += 3;
				break;
			case 15:
				mem[mem[itr+1]] = mem[REG(mem[itr+2])];
				itr += 3;
				break;
			case 16:
				mem[REG(mem[itr+1])] = REG(mem[itr+2]);
				itr += 3;
				break;
			case 17:
				myStack.push_back(itr+2);
				itr = REG(mem[itr+1]);
				break;
			case 18:
				if(myStack.empty())
					return 0;
				itr = myStack.back();
				myStack.pop_back();
				break;
			case 19:
				printf("%c", (char)REG(mem[itr+1]));
				itr += 2;
				break;
			case 20:
				scanf("%c", &mem[mem[itr+1]]);
				itr += 2;
				break;
			case 21:
				++itr;
				break;
			default:
				perror("Error: Bad Op\n");
				return 1;
		}
	}
}
