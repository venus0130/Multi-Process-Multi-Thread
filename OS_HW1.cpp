#include <iomanip>
#include <sstream>
#include <ctime>
#include <thread>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
/*#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/syscall.h>*/ 

using namespace std;
using namespace chrono;



struct Data
{
    string line;
    int num;
};

class OSone {
	public :
  		string mFileName;
  		bool Exit = false;
  		std::vector<int> aList; // a-?a?��a??a??a�VR

		int panel(int &k,int &method) {
		    cout << endl << "e??e?�Ma�K�Daa��a!?a??c�L�� : " << endl;
		    cin >> mFileName;
		    cout << "e??e?�Ma�K�Da??a??a1?a?? : " << endl;
		    cin >> k ;
		    cout << "e??e?�Ma�K�Da�V1a3�Ec�P�Le?? :(a�V1a3�E1,a�V1a3�E2,a�V1a3�E3,a�V1a3�E4)" << endl;
		    cin >> method;
		}
		
		void clear() {
		    aList.clear();
		}
		
		bool loadData() {
			struct Data test;
		    string line; // a��?e!?e3?e�L?
		    string number;
		    fstream fin;
		
		    fin.open((mFileName + ".txt").c_str(), ios::in);
		
		    if (! fin) {
		        cout << endl << mFileName << " does not exist! ###" << endl << endl;
		        return false;
		
		    }
		    else {
		            //getline(fin, number);  // eR��a??e!?e??
		
		      while (getline(fin, test.line, '\n')) {
		          const char*temp = test.line.c_str(); // a�K?a??stringe??a??const chara??a?�D!!!
		          int integer = atof (temp) ; ////// a??a??const chare??a??integera??a?�D!!!
		          aList.push_back(integer);
		
		          test.num++;
		      }
		
		    }
		
		        fin.close();
		            return true;
		  }
		
		void PrintShit () {
			for (int i = 0 ; i < aList.size() ; i++)
		      cout << aList.at(i) << endl;
		
		   }
		
		
		
		void Bubble() {
		    for (int i = 0; i < aList.size()-1; i++ ) {
		        for (int j = 0; j < aList.size()-1; j++) {
		            if (aList.at(j)> aList.at(j+1)) swap(aList.at(j), aList.at(j+1));
		        }
		    }
		
		    PrintShit();
		}
		
		void Bubble_slice_k(int k) {
		    int ListSize = aList.size();
		    int Ksize = ListSize / k;
		    if (ListSize % k != 0 ) Ksize++;
		    int Kmultipul = Ksize; // Ksize every round will include Ksize's multipul
		
		    int group = 1; // you can say how many group(must have one group)(i can't enter chinese fuck)
		    int i = 0;
		    int j = 0;
		    int tmp = 0;
		    int sub = 0; // sub array's number
		    while (Ksize <= aList.size()+1) {
		        if (Ksize == aList.size()+1) { //�p�GKsize = 10000, aList = 9999(�]�N�OListSize/k���l�ƪ����p) 
		            for (; i < (Ksize-1); i++ ) {  
		                for (j = Ksize-Kmultipul; j < Ksize; j++) 
		                    if ((j+1) < aList.size() && aList.at(j)> aList.at(j+1) ) swap(aList [j],aList [j+1]);
		            }
		        }
		        else {
		            for (; i < Ksize; i++ ) {
		                for ( j = Ksize-Kmultipul ; j < Ksize; j++) 
		                    if ( (j+1) < aList.size() && aList.at(j) > aList.at(j+1) ) swap(aList [j],aList [j+1]);          	
		            }				
		        }
		        i++; 
				j++;
		        group++;
		        Ksize = Kmultipul * group;
		    } //
		
		
		
		}
		
		const int Max = 1000;
		
		void Merge(int front, int mid, int end) {
		  std::vector<int> LeftSub(aList.begin()+front, aList.begin()+mid+1);
		  std::vector<int> RightSub(aList.begin()+mid+1, aList.begin()+end+1);
		
		  int idxLeft = 0, idxRight = 0, idxMerged = front;
		
		  while (idxLeft < LeftSub.size() && idxRight < RightSub.size()) {
		    if (LeftSub[idxLeft] <= RightSub[idxRight]) {
		      aList[idxMerged] = LeftSub[idxLeft];
		      idxLeft++;
		    } else {
		      aList[idxMerged] = RightSub[idxRight];
		      idxRight++;
		    }
		    idxMerged++;
		  }
		
		  // �B�z�Ѿl���� 
		  while (idxLeft < LeftSub.size()) {
		    aList[idxMerged] = LeftSub[idxLeft];
		    idxLeft++;
		    idxMerged++;
		  }
		
		  while (idxRight < RightSub.size()) {
		    aList[idxMerged] = RightSub[idxRight];
		    idxRight++;
		    idxMerged++;
		  }
		}
		
		void MergeSort(int front, int end){
		                                         // front�Pend���x�}�d��
		    if (front < end) {                   // ��ܥثe���x�}�d��O���Ī�
		        int mid = front+(end-front)/2;         // mid�Y�O�N�x�}��b����index
		        MergeSort(front, mid);    // �~��divide�x�}���e�b�qsubarray
		        MergeSort(mid+1, end);    // �~��divide�x�}����b�qsubarray
		        Merge(front, mid, end);   // �N���subarray�����, �æX�֥X�Ƨǫ᪺�x�}
		    }
		}
		
		bool Write(string &methodd,double cpuTime) {
			std::ofstream out((mFileName + "_output"+ methodd).c_str(), ios::app);
			for (auto &s : aList) {
	        	out << s << '\n';
	    	}
	    	string outTime = OutTime();
	    	out << "CPU Time : " << cpuTime << '\n';
	    	out << outTime << '\n';
	    	out.close();
	    	return 0;			
			
		}
		
		string OutTime() {
			
			std::string outTime;
			time_t now = time(nullptr); //�ɶ��W 
		    tm* utc_time = gmtime(&now); //�ରUTC 
		
		    utc_time->tm_hour += 8; //UTC+8 
		    if (utc_time->tm_hour >= 24) {
		        utc_time->tm_hour -= 24;
		        utc_time->tm_mday += 1;
		    }
		    if (utc_time->tm_mday > 31) {
		        utc_time->tm_mday -= 31;
		        utc_time->tm_mon += 1;
		    }
		    if (utc_time->tm_mon > 12) {
		        utc_time->tm_mon -= 12;
		        utc_time->tm_year += 1;
		    }
		

		    char buf[80];
		    strftime(buf, sizeof(buf), "%Y-%m-%d%H:%M:%S", utc_time); //�ର�r�Ŧ� 
				    
		    auto tp = chrono::system_clock::now(); // �@��n�B�~�� 
		    auto ms = chrono::duration_cast<chrono::microseconds>(tp.time_since_epoch()).count() % 1000000;
		

		    ostringstream oss; //UTC+8�M�@���X�� 
		    oss << buf << '.' << setfill('0') << setw(6) << ms << "+08:00";
		

		    //cout << "Output Time: " << oss.str() << endl;
			outTime = "Output Time : " + oss.str();
		    return outTime;
		}

};

  int main() {
	 std::clock_t start ;
	 std::clock_t end;
	 double cpuTime;
     int k,method;
     OSone os;
     os.panel(k,method);
     os.loadData();
	 std::string methodd = std::to_string(method);//���F�g�ɡA�ҥH���X�@��striing ���O��method 
 
     if (method == 1) {
     	start = std::clock(); //cpu time�_�l
        os.Bubble();
        end = std::clock(); //cpu time���� 
		cpuTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		os.Write(methodd,cpuTime);
        os.clear();
     } // 1

     else if (method == 2) {
     	start = std::clock(); //cpu time�_�l
        os.Bubble_slice_k(k);
        os.MergeSort(0,os.aList.size()-1);
		end = std::clock(); //cpu time���� 
		cpuTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		os.Write(methodd,cpuTime);
		os.clear();
     }
     

     //os.PrintShit();
  }

/////////////�o�Ӥ~�O�̷s!!!
 



