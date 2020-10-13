#include <iostream>
#include <vector>
#include <limits.h>
#include <math.h>
#include <float.h>

using namespace std;

// the iteration times
const int T = 5;

int N;
int K, D;

typedef struct Point {
	vector<double> datas;
	int cluster;
	Point(int D) {
		datas = vector<double>(D, 0);
		cluster = -1;
	}
	Point operator +(const Point& a) {
		Point res(this->datas.size());
		for (int i= 0; i< this->datas.size(); i++) {
			res.datas[i] = this->datas[i] + a.datas[i];
		}
		return res;
	}
	void operator +=(const Point& a) {
		for (int i= 0; i< this->datas.size(); i++) {
			this->datas[i] = this->datas[i] + a.datas[i];
		}
	}
	void devide(const int& a) {
		for (int i= 0; i< this->datas.size(); i++) {
			this->datas[i] = this->datas[i] / (double)a;
		}
	}
} Point;

void printPoints(vector<Point> v) {
	for (int i= 0; i< v.size(); i++) {
		for (int j= 0; j< v[i].datas.size(); j++) {
			cout<< v[i].datas[j]<< " ";
		}
		cout<< v[i].cluster<< endl;
	}
}

double cal_distance(Point& p1, Point& p2) {
	// Euclidean Distance
	double res = 0;
	for (int i= 0; i< D; i++) {
		double temp = (double) (p1.datas[i] - p2.datas[i]);
		res += temp * temp;
	}
	res = sqrt(res);
	return res;
}

void assign_to_center(Point& p, vector<Point>& clusters) {
	double min_d = DBL_MAX;
	int min_index = -1;
	for (int i= 0; i< clusters.size(); i++) {
		double d = cal_distance(p, clusters[i]);
		if (d < min_d) {
			min_d = d;
			min_index = i;
		}
	}
	p.cluster = min_index;
}

int main() {
	cout<< "please enter the dimension of the data points"<< endl;
	cin>> D;
	cout<< "please enter the num of data points"<< endl;
	cin>> N;
	vector<Point> points(N, Point(D));
	cout<< "please enter the data points"<< endl;
	for (int i= 0; i< N; i++) {
		for (int j= 0; j< D; j++) {
			cin>> points[i].datas[j];
		}
	}
	// printPoints(points);
	cout<< "please enter the cluster num K"<< endl;
	cin>> K;
	vector<Point> clusters = vector<Point>(K, Point(D));
	cout<< "please enter the initial means"<< endl;
	for (int i= 0; i< K; i++) {
		for (int j= 0; j< D; j++) {
			cin>> clusters[i].datas[j];
		}
		clusters[i].cluster = i;
	}
	// printPoints(clusters);
	for (int t = 0; t < T; t++) {
		/*
			assign the points to according centers.
		*/
		for (int i= 0; i< N; i++) {
			assign_to_center(points[i], clusters);
		}
		/*
			recal the clusters.
		*/
		vector<int> c_count = vector<int>(K, 0);
		for (int i= 0; i< K; i++) {
			clusters[i].datas.assign(D, 0.0);
		}
		for (int i= 0; i< N; i++) {
			int c = points[i].cluster;
			++c_count[c];
			clusters[c] += points[i];
		}
		for (int i= 0; i< K; i++) {
			clusters[i].devide(c_count[i]);
		}
		// print each step
		cout<< endl;
		cout<< "T = "<< t<< endl;
		cout<< "PRINT POINTS"<< endl;
		printPoints(points);
		cout<< "PRINT CLUSTERS"<< endl; 
		printPoints(clusters);
	}
}
