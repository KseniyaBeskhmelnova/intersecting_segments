#include "Service.h"
#include "Tree23.h"
#include "AVLTree.h"

bool Service::intersectNaive(std::vector<Segment> segmentsArray, size_t arrSize) {
	bool intersect = false;
	for (int i = 0; i < arrSize - 1; i ++) {
		for (int j = i + 1; j < arrSize; j ++) {
			if (segmentsArray[i].intersects(segmentsArray[j])) {
				intersect = true;
				break;
			}
		}
		if (intersect)
			break;
	}
	return intersect;
}

bool Service::intersectEffectiveTree23(std::vector<Segment> segmentsArray, size_t arrSize) {
	int size = arrSize * 2;
	bool intersect = false;
	TwoThreeTree<Segment> tree;
	Service::sort(segmentsArray, 0, size - 1, Segment::compareByX);
	for (int i = 0; i < size; i++) {
		Segment::updateCurrentX(segmentsArray[i]);
		if (segmentsArray[i].getCmpPoint() == Segment::START) {
			tree.insert(segmentsArray[i]);
			intersect = segmentsArray[i].intersects(tree.findPredecessor(segmentsArray[i]));
			if (intersect)
				break;
			intersect = segmentsArray[i].intersects(tree.findSuccessor(segmentsArray[i]));
			if (intersect)
				break;
		}
		else if (segmentsArray[i].getCmpPoint() == Segment::END) {
			intersect = tree.findPredecessor(segmentsArray[i]).intersects(tree.findSuccessor(segmentsArray[i]));
			if (intersect)
				break;
			tree.remove(segmentsArray[i]);
		}
	}
	return intersect;
}

bool Service::intersectEffectiveAVLTree(std::vector<Segment> segmentsArray, size_t arrSize) {
	int size = arrSize * 2;
	bool intersect = false;
	AVLTree<Segment> tree;
	Service::sort(segmentsArray, 0, size - 1, Segment::compareByX);
	for (int i = 0; i < size; i++) {
		Segment::updateCurrentX(segmentsArray[i]);
		if (segmentsArray[i].getCmpPoint() == Segment::START) {
			tree.insert(segmentsArray[i]);
			intersect = segmentsArray[i].intersects(tree.findPredecessor(segmentsArray[i]));
			if (intersect)
				break;
			intersect = segmentsArray[i].intersects(tree.findSuccessor(segmentsArray[i]));
			if (intersect)
				break;
		}
		else if (segmentsArray[i].getCmpPoint() == Segment::END) {
			intersect = tree.findPredecessor(segmentsArray[i]).intersects(tree.findSuccessor(segmentsArray[i]));
			if (intersect)
				break;
			tree.remove(segmentsArray[i]);
		}
	}
	return intersect;
}

bool Service::intersect(std::vector<Segment> segmentsArray, size_t arrSize, Segment& segment) {
	bool intersect = false;
	for (int i = 0; i < arrSize; i += 2) {
		if (segment.intersects(segmentsArray[i])) {
			intersect = true;
			break;
		}
	}
	return intersect;
}

void generatePointsRand(double& x1, double& x2, double& y1, double& y2) {
	x1 = (double)rand() / RAND_MAX;
	x2 = (double)rand() / RAND_MAX;
	y1 = (double)rand() / RAND_MAX;
	y2 = (double)rand() / RAND_MAX;
}

void generatePointsRandWithRadius(double& x1, double& x2, double& y1, double& y2, double radius)
{
	double x_center = (double)rand() / RAND_MAX;
	double y_center = (double)rand() / RAND_MAX;
	double angle = M_PI * (double)rand() / RAND_MAX;

	x1 = x_center - radius * std::cos(angle) / 2.0;
	x2 = x_center + radius * std::cos(angle) / 2.0;
	y1 = y_center - radius * std::sin(angle) / 2.0;
	y2 = y_center + radius * std::sin(angle) / 2.0;
}

std::vector<Segment> Service::randomSegments(size_t size) {
	std::vector<Segment> SegmentsArray(size * 2);
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for (size_t i = 0; i < size; ++i) {
		double x1, x2, y1, y2;
		generatePointsRand(x1, x2, y1, y2);
		if (x2 < x1)
			std::swap(x2, x1);
		SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
		SegmentsArray[i * 2 + 1] = Segment(Point(x1, y1), Point(x2, y2), Segment::END);
	}
	return SegmentsArray;
}


std::vector<Segment> Service::randomSegments(size_t size, int K) {
	std::vector<Segment> SegmentsArray(size * 2);
	std::srand((unsigned int)std::time(nullptr));
	for (int i = 0; i < size; ++i) {
		double x1, x2, y1, y2;
		generatePointsRand(x1, x2, y1, y2);
		if (x2 < x1)
			swap(x2, x1);
		SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
		if (i == K) {
			while (!SegmentsArray[i * 2].intersects(SegmentsArray[(i - 1) * 2]) ||
				intersect(SegmentsArray, i * 2 - 2, SegmentsArray[i * 2]))
			{
				generatePointsRand(x1, x2, y1, y2);
				if (x2 < x1)
					swap(x2, x1);

				SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
			}
		}
		else {
			while (intersect(SegmentsArray, i * 2, SegmentsArray[i * 2])) {
				generatePointsRand(x1, x2, y1, y2);
				if (x2 < x1)
					swap(x2, x1);
				SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
			}
		}
		SegmentsArray[i * 2 + 1] = Segment(Point(x1, y1), Point(x2, y2), Segment::END);
	}
	return SegmentsArray;
}

std::vector<Segment> Service::randomSegments(size_t size, double radius) {
	std::vector<Segment> SegmentsArray(size * 2);
	std::srand((unsigned int)std::time(nullptr));
	for (int i = 0; i < size; ++i) {
		double x1, x2, y1, y2;
		generatePointsRandWithRadius(x1, x2, y1, y2, radius);
		if (x2 < x1)
			swap(x2, x1);
		SegmentsArray[i * 2] = Segment(Point(x1, y1), Point(x2, y2), Segment::START);
		SegmentsArray[i * 2 + 1] = Segment(Point(x1, y1), Point(x2, y2), Segment::END);
	}
	return SegmentsArray;
}