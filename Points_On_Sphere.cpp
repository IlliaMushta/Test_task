#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>

#define PI 3.14159265

class Point
{
private:
	int theta_d;
	int phi_d;

public:
	Point(int theta = 0, int phi = 0) : theta_d(theta), phi_d(phi)
	{

	}

	void setTheta(int theta) {
		theta_d = theta;
	}

	void setPhi(int phi) {
		phi_d = phi;
	}

	int getTheta() const{
		return theta_d;
	}

	int getPhi() const {
		return phi_d;
	}

	friend double distance (const Point &point1, const Point &point2);
	friend std::ostream& operator<< (std::ostream &out, const Point &point);
};

//The arc length on a sphere of radius r = 1 through central angle given in radians
double distance(const Point &point1, const Point &point2) {
	return acos(sin((90-point1.getTheta())*PI / 180)*sin((90-point2.getTheta())*PI / 180) + cos((90-point1.getTheta())*PI / 180)*cos((90-point2.getTheta())*PI / 180)*cos(abs(point1.getPhi() - point2.getPhi())*PI / 180));
}

std::ostream& operator<< (std::ostream &out, const Point &point)
{
	out << "Theta:" << point.getTheta() << std::endl;
	out << "Phi:" << point.getPhi() << std::endl;

	return out;
}

void printPoints(const Point *point, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << point[i] << std::endl;
	}
}

bool comparePhi(Point &point1, Point &point2) {
	if (point1.getPhi() <= 180 && point2.getPhi() <= 180) {
		return (point1.getPhi() <= point2.getPhi());
	}
	else if (point1.getPhi() <= 180 && point2.getPhi() > 180) {
		return (point1.getPhi() <= (360 - point2.getPhi()));
	}
	else if (point1.getPhi() > 180 && point2.getPhi() <= 180) {
		return ((360 - point1.getPhi()) <= point2.getPhi());
	}
	else if (point1.getPhi() > 180 && point2.getPhi() > 180) {
		return ((360 - point1.getPhi()) <= (360 - point2.getPhi()));
	}
	return 0;
}

void merge(Point *point, int const left, int const mid, int const right, std::string coordinate)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	Point *leftArray = new Point[subArrayOne];
	Point *rightArray = new Point[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++) {
		leftArray[i].setTheta(point[left + i].getTheta());
		leftArray[i].setPhi(point[left + i].getPhi());
	}

	for (auto j = 0; j < subArrayTwo; j++) {
		rightArray[j].setTheta(point[mid + 1 + j].getTheta());
		rightArray[j].setPhi(point[mid + 1 + j].getPhi());
	}

	auto indexOfSubArrayOne = 0, 
		indexOfSubArrayTwo = 0; 
	int indexOfMergedArray = left; 

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (coordinate == "Theta") {
			if (leftArray[indexOfSubArrayOne].getTheta() <= rightArray[indexOfSubArrayTwo].getTheta()) {
				point[indexOfMergedArray].setTheta(leftArray[indexOfSubArrayOne].getTheta());
				point[indexOfMergedArray].setPhi(leftArray[indexOfSubArrayOne].getPhi());
				indexOfSubArrayOne++;
			}
			else {
				point[indexOfMergedArray].setTheta(rightArray[indexOfSubArrayTwo].getTheta());
				point[indexOfMergedArray].setPhi(rightArray[indexOfSubArrayTwo].getPhi());
				indexOfSubArrayTwo++;
			}
		}
		else if (coordinate == "Phi") {
		
			if (comparePhi(leftArray[indexOfSubArrayOne],rightArray[indexOfSubArrayTwo])) {
				point[indexOfMergedArray].setTheta(leftArray[indexOfSubArrayOne].getTheta());
				point[indexOfMergedArray].setPhi(leftArray[indexOfSubArrayOne].getPhi());
				indexOfSubArrayOne++;
			}
			else {
				point[indexOfMergedArray].setTheta(rightArray[indexOfSubArrayTwo].getTheta());
				point[indexOfMergedArray].setPhi(rightArray[indexOfSubArrayTwo].getPhi());
				indexOfSubArrayTwo++;
			}
		}
		
		indexOfMergedArray++;
	}
	
	while (indexOfSubArrayOne < subArrayOne) {
		point[indexOfMergedArray].setTheta(leftArray[indexOfSubArrayOne].getTheta());
		point[indexOfMergedArray].setPhi(leftArray[indexOfSubArrayOne].getPhi());
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	
	while (indexOfSubArrayTwo < subArrayTwo) {
		point[indexOfMergedArray].setTheta(rightArray[indexOfSubArrayTwo].getTheta());
		point[indexOfMergedArray].setPhi(rightArray[indexOfSubArrayTwo].getPhi());
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}

	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(Point *point, int const begin, int const end, std::string coordinate)
{
	if (begin >= end)
		return; 

	auto mid = begin + (end - begin) / 2;
	mergeSort(point, begin, mid, coordinate);
	mergeSort(point, mid + 1, end, coordinate);
	merge(point, begin, mid, end, coordinate);
}


double min_distance_slow(Point * point, int size, std::vector<Point> &closest_pair) {
	double min_distance = distance(point[0], point[1]);

	for (int i = 0; i < size; i++) {
		for (int j = i+1; j < size; j++) {
			double temp_min_distance = distance(point[i], point[j]);
	
			if (temp_min_distance < min_distance) {
				min_distance = temp_min_distance;
				closest_pair[0] = point[i];
				closest_pair[1] = point[j];
			}
		}
	}

	return min_distance;
}

void splitPoints(Point *point,int size, Point &sortedPhi, Point *pointL, Point *pointR) {
	int i = 0;
	int j = 0;
	int parts_size = size / 2;
	for (int k = 0; k < size; k++) {
		if (comparePhi(point[k],sortedPhi)) {
			if (i < parts_size) {
				pointL[i++] = point[k];
			}
			else {
				if (j < parts_size) {
					pointR[j++] = point[k];
				}
			}
		}
		else {
			if (j < parts_size) {
				pointR[j++] = point[k];
			}
			else {
				if (i < parts_size) {
					pointL[i++] = point[k];
				}
			}
		}
	}
}

bool isInStripe(Point &point, Point &mid, double min_dist) {
	if (point.getTheta() <= 90) {
	
		return ((acos(sin((90 - point.getTheta())*PI / 180)*sin((90 - point.getTheta())*PI / 180) + cos((90 - point.getTheta())*PI / 180)*cos((90 - point.getTheta())*PI / 180)*cos(abs(point.getPhi() - (mid.getPhi()+180))*PI / 180)) <= min_dist) || (acos(sin((90 - point.getTheta())*PI / 180)*sin((90 - point.getTheta())*PI / 180) + cos((90 - point.getTheta())*PI / 180)*cos((90 - point.getTheta())*PI / 180)*cos(abs(point.getPhi() - mid.getPhi())*PI / 180)) <= min_dist) || (acos(sin((90 - point.getTheta())*PI / 180)*sin((90 - 0)*PI / 180) + cos((90 - point.getTheta())*PI / 180)*cos((90 - 0)*PI / 180)*cos(0 * PI / 180)) <= min_dist));
	}
	else if (point.getTheta() > 90) {
		
		return ((acos(sin((90 - point.getTheta())*PI / 180)*sin((90 - point.getTheta())*PI / 180) + cos((90 - point.getTheta())*PI / 180)*cos((90 - point.getTheta())*PI / 180)*cos(abs(point.getPhi() - (mid.getPhi()+180))*PI / 180)) <= min_dist) || (acos(sin((90 - point.getTheta())*PI / 180)*sin((90 - point.getTheta())*PI / 180) + cos((90 - point.getTheta())*PI / 180)*cos((90 - point.getTheta())*PI / 180)*cos(abs(point.getPhi() - mid.getPhi())*PI / 180)) <= min_dist) || (acos(sin((90 - point.getTheta())*PI / 180)*sin((-90 - 0)*PI / 180) + cos((90 - point.getTheta())*PI / 180)*cos((-90 - 0)*PI / 180)*cos(0 * PI / 180)) <= min_dist));
	}
	return 0;
}

double merge_distances(double min_dist, int size, Point &mid, Point *sortedTheta, std::vector<Point> &closest_pair) {
	std::vector<Point> interested_points;
	for (int i = 0; i < size; i++) {
		if(isInStripe(sortedTheta[i],mid,min_dist)){
			interested_points.push_back(sortedTheta[i]);
		}
	}
	for (int i = 0; i < interested_points.size(); i++) {
		for (int j = i + 1; j < interested_points.size(); j++) {
			if (acos(sin((90 - interested_points[i].getTheta())*PI / 180)*sin((90 - interested_points[j].getTheta())*PI / 180) + cos((90 - interested_points[i].getTheta())*PI / 180)*cos((90 - interested_points[j].getTheta())*PI / 180)*cos(0*PI / 180)) > min_dist)
				break;

			if (distance(interested_points[i], interested_points[j]) < min_dist) {
				closest_pair[0] = interested_points[i];
				closest_pair[1] = interested_points[j];
				min_dist = distance(interested_points[i], interested_points[j]);
			}
		}
	}

	return min_dist;
}

double min_distance(Point *sortedTheta, Point *sortedPhi, int size, std::vector<Point> &closest_pair) {
	if (size == 1) {
		return PI;
	}else if (size == 2){
		closest_pair[0] = sortedTheta[0];
		closest_pair[1] = sortedTheta[1];
		return distance(sortedTheta[0], sortedTheta[1]);
	}
	else {
		int mid = size / 2;
		Point *pointL = new Point[mid];
		Point *pointR = new Point[size - mid];
		
		splitPoints(sortedTheta, size, sortedPhi[mid - 1], pointL, pointR);
		
		std::vector<Point> closest_pairL(2);
		std::vector<Point> closest_pairR(2);

		double distL = min_distance(pointL, sortedPhi, mid, closest_pairL);
		double distR = min_distance(pointR, sortedPhi + mid, size - mid, closest_pairR);

		delete[] pointL;
		delete[] pointR;
		double min_dist = 0;
		if (distL < distR) {
			min_dist = distL;
			closest_pair = closest_pairL;
		}
		else {
			min_dist = distR;
			closest_pair = closest_pairR;
		}

		return  merge_distances(min_dist, size, sortedPhi[mid - 1], sortedTheta, closest_pair);
	}
}

double pairPointsWithMinDistance(Point *point, int number_of_points, std::vector<Point> &closest_pair) {
	Point *sortedTheta = new Point[number_of_points];
	Point *sortedPhi = new Point[number_of_points];
	for (int i = 0; i < number_of_points; i++) {
		sortedTheta[i] = point[i];
		sortedPhi[i] = point[i];
	}
	mergeSort(sortedTheta, 0, number_of_points - 1, "Theta");
	mergeSort(sortedPhi, 0, number_of_points - 1, "Phi");

	double result = min_distance(sortedTheta, sortedPhi, number_of_points, closest_pair);

	delete[] sortedTheta;
	delete[] sortedPhi;
	return  result; 
}


int main()
{	
	srand((unsigned int)time(0));

	int number_of_points = rand() % 100 + 2;
	Point *point = new Point[number_of_points];
	for (int i = 0; i < number_of_points; i++) {
		point[i].setTheta(rand() % 180);
		point[i].setPhi(rand() % 359);
	}

	std::vector<Point> closest_pair(2);

	double res_fast = pairPointsWithMinDistance(point, number_of_points, closest_pair);
	std::cout << "---------------closest_pair--------------" << std::endl;
	std::cout << closest_pair[0] << std::endl;
	std::cout << closest_pair[1] << std::endl;
	std::cout << "distance=" << res_fast << std::endl;

	delete[] point;

	return 0;
}

