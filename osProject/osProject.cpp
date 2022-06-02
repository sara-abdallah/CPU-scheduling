#include <iostream>
#include<cmath>
#include<algorithm>
#include<string>
#include<vector>
#include<utility>
#define ll long long int
using namespace std;
void fcfs(vector<pair<string, pair<int, ll>>>v , int numProcess, ll sumBrust) {
	cout << "\nGantt Chart:" << endl;
	cout << "|";
	int x = 0;
	ll  inTime = v[0].second.first;
	vector <pair<string, ll>>wt(numProcess);
	for (int j = 0; j <= sumBrust && x < numProcess; j++) {
		if (j >= v[x].second.first) {
			cout << " " << v[x].first << " " << "|";
			wt[x].first = v[x].first;
			wt[x].second = inTime - v[x].second.first;
			inTime += v[x].second.second;
			j = inTime;
			x++;
		}
		else {
			cout << " idle " << "|";
		}
	}
	cout << "\n";
	cout << "\nWaiting Time:" << endl;
	double t = 0;
	for (size_t i = 0; i < numProcess; i++) {
		cout << wt[i].first << " = " << wt[i].second << endl;
		t += wt[i].second;
	}
	cout << "Averrage Wating Time = " << (t / numProcess) << endl;
}
void sjfnp(vector<pair<string, pair<int, ll>>>v, int numProcess, ll sumBrust) {
	cout << "\nGantt Chart:" << endl;
	cout << "|";
	vector<pair<string, pair<int, ll>>>svs(numProcess);
	svs = v;
	////// عملنا فيكتور جديد هنحط فيه نفس عناصر الفيكتور القديم وهنرتبهم ع حسب مين البرست بتاعه اقل //////
	for (size_t j = 1; j < numProcess; j++) {
		for (size_t i = 0; i < numProcess; i++) {
			if (svs[j].second.second < svs[i].second.second) {
				swap(svs[j], svs[i]);
			}
		}
	}

	int x = 0;
	bool found = false;
	ll  inTime = v[0].second.first;
	vector <pair<string, ll>>wt(numProcess);
	for (int j = 0;j <= sumBrust; j++) {
		
		for (size_t i = x; i < numProcess; i++) {
			if (j >= svs[i].second.first) {
				cout << " " << svs[i].first << " "<< "|";
				wt[x].first = svs[i].first;
				wt[x].second = inTime - svs[i].second.first;
				inTime += svs[i].second.second;
				j = inTime - 1;   ///نقصنا واحد عشان اللوب فوق هتزوده الواحد دا ///
				swap(svs[i], svs[x]);
				found = true;
				x++;
				break;
			}
		}
			
		if (!found) {
			cout<< " idle " << "|";
		}
	}
	cout << "\n";
	cout << "\nWaiting Time:" << endl;
	double t = 0;
	for (size_t i = 0; i < numProcess; i++) {
		cout << wt[i].first << " = " << wt[i].second << endl;
		t += wt[i].second;
	}
	cout << "Averrage Wating Time = " << (t / numProcess) << endl;
}
void sjfp(vector<pair<string, pair<int, ll>>>v, int n, ll sumBrust) {
	cout << "\nGantt Chart:" << endl;
	cout << "|";
	int rt[100000];
	for (int i = 0; i < n; i++) {
		rt[i] = v[i].second.second;
	}
	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	bool check = false;
	ll  inTime = v[0].second.first;//دا الوقت بتاعي 
	vector <pair<string,ll>>wt(n);
	while (complete != n) 
	{
		for (int j = 0; j < n; j++) 
		{
			if ((v[j].second.first <= t) && (rt[j] < minm) && (rt[j] > 0)) { 
				cout << " " << v[j].first << " " << "|";
				minm = rt[j];
				shortest = j;
				check = true;
			}
		}
		if (check == false) {
			cout << " idle " << "|";
			t++;
			continue;
		}
		rt[shortest]--;
		minm = rt[shortest];
		if (minm == 0)
			minm = INT_MAX;
		if (rt[shortest] == 0) {
			complete++;
			check = false;
			finish_time = t + 1;
			wt[shortest].first = v[shortest].first;
			wt[shortest].second = finish_time - v[shortest].second.second - v[shortest].second.first;
			if (wt[shortest].second < 0) {
				wt[shortest].second = 0;
			}
		}
		t++;
	}
	cout << "\n";
	cout << "\nWaiting Time:" << endl;
	double tt = 0;
	for (size_t i = 0; i < n; i++) {
		cout << wt[i].first << " = " << wt[i].second << endl;
		tt += wt[i].second;
	}
	cout << "Averrage Wating Time = " << (tt / n) << endl;
}
void RR(vector<pair<string, pair<int, ll>>>v, int numProcess, ll sumBrust, int q) 
{
	cout << "\nGantt Chart:" << endl;
	cout << "|";
	int x = 0;
	bool found = false;
	ll  inTime = v[0].second.first;  //دا الوقت بتاعي 
	vector <pair<string, pair<ll, ll>>>wt(numProcess);
	for (size_t i = 0; i < numProcess; i++) {// بندي للفيكتور قيم ابتدائية
		wt[i].first = " ";
		wt[i].second.first = 0;
		wt[i].second.second = v[i].second.first;//بديلوا قيمة ابتدائية الوقت اللي وصلت فيه وبعدين هياخد الوقت اللي طلع فيه
	}
	for (int j = 0; j <= sumBrust; j++) {
		if (x == numProcess) {//عملنا كدا عشان لما نوصل لنهاية الجدول نعيده تاني يعني بنعمل كدا لو عندي 3 عمليات (0\1\2\0\1\2\وهكذا)
			x = 0;
		}
		for (size_t i = x; i < numProcess; i++) {
			if (j >= v[i].second.first) {
				if (v[i].second.second > 0) {
					cout << " " << v[i].first << " " << "|";
					wt[x].first = v[i].first;
					wt[x].second.first += inTime - wt[x].second.second;
					wt[x].second.second = inTime + q;// عملنا زي مقلنا فوق اخدت القيمة اللي طلعت فيه 
					if (v[i].second.second < q) {
						inTime += v[i].second.second;
					}
					else {
						inTime += q;
					}
					v[i].second.second -= q;
					j = inTime - 1;
					found = true;
					x++;
					break;
				}
				else {
					x++;
					break;
				}
			}
		}
		if (!found) {
			cout << " idle " << "|";
		}
	}
	cout << "\n";
	cout << "\nWaiting Time:" << endl;
	double t = 0;
	for (size_t i = 0; i < numProcess; i++) {
		cout << wt[i].first << " = " << wt[i].second.first << endl;
		t += wt[i].second.first;
	}
	cout << "Averrage Wating Time = " << (t / numProcess) << endl;

}
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

////////////////////////////// بداية الكود ////////////////////////////////////////////
	vector<pair<string, pair<int, ll>>>v(100000);  //بنخزن ف فيكتور
	int numProcess;  //عدد العمليات
	ll sumBrust = 0; //مجموع البرست بتاع العمليات كلها
	int ch;

	cout << "Choice the algorithm you want to make schedule:" << endl;
	cout << "choice 1 :First Come First Served Scheduler" << endl;
	cout << "choice 2 :Shortest Job First non-preemptive Scheduler" << endl;
	cout << "choice 3 :Shortest Job First preemptive Scheduler" << endl;
	cout << "choice 4 :Round-Robin Scheduler" << endl;
	cout << "choice 5 :Exit" << endl;

	cout << "Your choice =";
	cin >> ch;

	if (ch == 5) {
		exit;
	}
	else {
		cout << "Enter The Number Of Process =";
		cin >> numProcess;
		cout << "Enter Process, ArriveTime and Brust" << endl;
		for (int i = 0; i < numProcess; i++) {
			cin >> v[i].first >> v[i].second.first >> v[i].second.second;  //هنا بنخزن ف الفيكتور
			sumBrust += v[i].second.second; //بنحسب البرست الكلي عشان هنحتاجه بعدين
		}
		/////// sort vector علي حسب مين جه الاول////////////////
		for (size_t j = 1; j < numProcess; j++) {
			for (size_t i = 0; i < numProcess; i++) {
				if (v[j].second.first < v[i].second.first) {
					swap(v[j], v[i]);
				}
			}
		}

		if (ch == 1) {  // fcfc scheduling
			fcfs(v, numProcess, sumBrust + 1);
		}
		else if (ch == 2) {  // sjf np scheduling
			sjfnp(v, numProcess, sumBrust + 1);
		}
		else if (ch == 3) {  // sjf p scheduling
			sjfp(v, numProcess, sumBrust + 1);
		}
		else {  // RR scheduling
			int q;
			cout << "Enter time quantum =";
			cin >> q;
			RR(v, numProcess, sumBrust + 1, q);
		}
	}
	
}
