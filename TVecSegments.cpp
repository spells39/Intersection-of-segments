#include "TVecSegments.h"

/*VecSeg::VecSeg(const VecSeg& s)
{
	segs = s.segs;
}*/

void VecSeg::pushback(Segment seg_)
{
	seg_.setSegIndex(static_cast<int>(getLength()));
	segs.push_back(seg_);
	points.push_back(seg_.getBegin());
	points.push_back(seg_.getEnd());
}

bool VecSeg::interBeforeK(const Segment& seg_, int k)
{
	bool inter = false;
	for(int i = 0; i < k + 2 && i < segs.size(); i++)
		if (seg_ == segs[i] || intersection(seg_, segs[i]))
		{
			inter = true;
			continue;
		}
	return inter;
}

bool VecSeg::interWithoutLast(const Segment& seg_, int k)
{
	return interBeforeK(seg_, k - 2);
}

bool intersection(const Segment& a, const Segment& b)
{
	Point aP1 = a.getBegin();
	Point bP1 = b.getBegin();
	Point aP2 = a.getEnd();
	Point bP2 = b.getEnd();
	Vector vec1(aP2 - aP1), vec2(bP2 - bP1);
	Vector v1(bP1 - aP1), v2(bP2 - aP1);
	Vector prod1(vec1 * v1), prod2(vec1 * v2);
	if (prod1.z() > 0 && prod2.z() > 0 || prod1.z() < 0 && prod2.z() < 0)
		return false;
	Vector v3(aP1 - bP1), v4(aP2 - bP1);
	prod1 = vec2 * v3; prod2 = vec2 * v4;
	if (prod1.z() > 0 && prod2.z() > 0 || prod1.z() < 0 && prod2.z() < 0)
		return false;
	return true;
}

/*bool VecSeg::onSeg(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}

int VecSeg::orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return 0;
	return (val > 0) ? 1 : 2;
}

bool VecSeg::doIntersect(const Segment& a, const Segment& b)
{
	Point p1 = a.getBegin(), q1 = a.getEnd(), p2 = b.getBegin(), q2 = b.getEnd();
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);
	if (o1 != o2 && o3 != o4)
		return true;
	if (o1 == 0 && onSeg(p1, p2, q1))
		return true;
	if (o2 == 0 && onSeg(p1, q2, q1))
		return true;
	if (o3 == 0 && onSeg(p2, p1, q2))
		return true;
	if (o4 == 0 && onSeg(p2, q1, q2))
		return true;
	return false;
}*/

int VecSeg::partition(int l, int r)
{
	/*Point pivot = points[right];
	int wall = left;
	for(int i = left; i <= right - 1; i++)
		if (points[i] <= pivot)
		{
			std::swap(points[i], points[wall]);
			wall++;
		}
	std::swap(points[wall], points[right]);
	return wall;*/
	Point pivot = points[r];
	int wall = l;
	for(int i = l; i <= r - 1; i++)
		if (points[i] <= pivot)
		{
			std::swap(points[i], points[wall]);
			wall++;
		}
	std::swap(points[wall], points[r]);
	return wall;
}

Segment* VecSeg::randCreateSeg(int w)
{
	double x1 = (double)rand() / RAND_MAX * w;
	double x2 = (double)rand() / RAND_MAX * w;
	double y1 = (double)rand() / RAND_MAX * w;
	double y2 = (double)rand() / RAND_MAX * w;
	while (x2 == x1)
		x2 = (double)rand() / RAND_MAX * w;
	Point p1(x1, y1), p2(x2, y2);
	p1.segIndex = getLength();
	p2.segIndex = getLength();
	return new Segment(p1, p2);
}

Segment* VecSeg::randSegByLength(double length)
{
	int angle = r(-90, 90);
	while (angle == 90)
		angle = r(-90, 90);
	angle *= M_PI / 180;
	double midX = (double)rand() / RAND_MAX;
	double midY = (double)rand() / RAND_MAX;
	double x1 = midX - length * std::cos(angle) / 2.0;
	double x2 = midX + length * std::cos(angle) / 2.0;
	double y1 = midY - length * std::sin(angle) / 2.0;
	double y2 = midY + length * std::sin(angle) / 2.0;
	Point p1(x1, y1), p2(x2, y2);
	p1.segIndex = getLength();
	p2.segIndex = getLength();
	return new Segment(p1, p2);
}

void VecSeg::createRSByPoints(int n, int k, int w)
{
	clear();
	if (n == 0)
	{
		pushback(*randCreateSeg(w));
		return;
	}
	if (n < 0 || k < -1 || k >= n - 1)
		throw - 1;
	if (n == 1)
	{
		return;
	}
	if (k == -1)
		k = n - 2;
	Segment* seg_;
	for (int i = 0; i < n; ++i)
	{
		seg_ = randCreateSeg(w);
		//cout << "k = " << k << " i = " << i << endl;
		if (i == k + 1)
		{
			while (!intersection(*seg_, segs.back()) || interWithoutLast(*seg_, k))
			{
				delete seg_;
				seg_ = randCreateSeg(w);
			}
		}
		else
			while (interBeforeK(*seg_, k))
			{
				delete seg_;
				seg_ = randCreateSeg(w);
			}
		pushback(*seg_);
		delete seg_;
	}

	/*for (i = 0; i < k + 1; ++i)
	{
		Segment* seg = randCreateSeg(w);
		bool res = false;
		for (const auto& segment : segs)
		{
			if (*seg == segment || intersection(*seg, segment))
			{
				res = true;
				break;
			}
		}

		if (res)
			i--;
		else
			pushback(*seg);
		delete seg;
	}
	Segment* seg = randCreateSeg();
	while (*seg == segs.back() || !intersection(*seg, segs.back()))
	{
		delete seg;
		seg = randCreateSeg();
	}
	pushback(*seg);
	i++;
	delete seg;
	while (i < n - 1)
	{
		pushback(*randCreateSeg());
		i++;
	}*/
}

void VecSeg::createRSByLength(double len, int n)
{
	clear();
	Segment* seg;
	for (int i = 0; i < n; i++)
	{
		seg = randSegByLength(len);
		pushback(*seg);
		delete seg;
	}
}

void VecSeg::sortPoints(int l, int r)
{
	if (l < r)
	{
		int curr = partition(l, r);
		sortPoints(l, curr - 1);
		sortPoints(curr + 1, r);
	}
}

void VecSeg::printS()
{
	for (auto& elem : segs)
	{
		cout << elem << endl;
		cout << "----------------" << endl;
	}
}

void VecSeg::clear()
{
	points.clear();
	segs.clear();
}

bool VecSeg::intersecNaive()
{
	bool res = false;
	for (int i = 0; i < getLength() - 1; i++)
	{
		for(int j = i + 1; j < getLength(); j++)
			if (intersection(segs[i], segs[j]))
			{
				cout << "Naive" << endl;
				cout << segs[i] << endl;
				cout << segs[j] << endl;
				res = true;
				break;
			}
		if (res)
			break;
	}
	return res;
}

bool VecSeg::intersecEf()
{
	/*Tree tr;
	bool res = false;
	int count = 0;
	for (auto p : points)
	{
		count++;
		Segment s = segs[p.segIndex];
		if (s.getBegin().x == s.getEnd().x)
			continue;
		if (p.isLeft)
		{
			Node* addSeg = tr.insert(tr.getRoot(), s);
			Segment sPrev = tr.getPrev(addSeg);
			res = intersection(s, sPrev);
			if (!(s == sPrev))
			{
				if (res)
				{
					cout << "Effective" << endl;
					cout << s << endl;
					cout << sPrev << endl;
					cout << "count = " << count << endl;
					break;
				}
			}
			Segment sNext = tr.getNext(addSeg);
			res = intersection(s, sNext);
			if (!(s == sNext))
			{
				if (res)
				{
					cout << "Effective" << endl;
					cout << s << endl;
					cout << sNext << endl;
					cout << "count = " << count << endl;
					break;
				}
			}
		}
		else
		{
			Node* node = tr.search(tr.getRoot(), s, p.x);
			if (node == nullptr)
				continue;
			Segment sPrev = tr.getPrev(node);
			Segment sNext = tr.getNext(node);
			res = intersection(sPrev, sNext);
			if (!(sPrev == sNext))
			{
				if (res)
				{
					cout << "Effective" << endl;
					cout << sPrev << endl;
					cout << sNext << endl;
					cout << "count = " << count << endl;
					break;
				}
			}
			tr.remove(s);
			if (tr.search(tr.getRoot(), s, p.x))
				continue;
		}
	}
	return res;*/
	if (points.empty())
		return false;
	Tree tr;
	bool res = false;
	for (auto p : points)
	{
		Segment s = segs[p.segIndex];
		if (s.getBegin().x == s.getEnd().x)
			throw std::runtime_error("Segs with same x");
		if (p.isLeft)
		{
			tr.insert(tr.getRoot(), s);
			Node* addSeg = tr.search(tr.getRoot(), s, s.getBegin().x);
			Segment prevSeg = tr.getPrev(addSeg);
			res = intersection(s, prevSeg);
			if (s == prevSeg)
				throw std::runtime_error("Identical segs detected");
			if (res)
			{
				cout << "Effective" << endl;
				cout << s << endl;
				cout << prevSeg << endl;
				break;
			}
			Segment nextSeg = tr.getNext(addSeg);
			res = intersection(s, nextSeg);
			if (s == nextSeg)
				throw std::runtime_error("Identical segs detected");
			if (res)
			{
				cout << "Effective" << endl;
				cout << s << endl;
				cout << nextSeg << endl;
				break;
			}
		}
		else
		{
			Node* node = tr.search(tr.getRoot(), s, p.x);
			if (!node)
				node = tr.search(tr.getRoot(), s, p.x);
				//throw std::runtime_error("Node not found in the tree");
			if (s != node->seg)
				throw std::runtime_error("Invalid seg in the node");
			Segment prevSeg = tr.getPrev(node);
			Segment nextSeg = tr.getNext(node);
			res = intersection(prevSeg, nextSeg);
			if (prevSeg == nextSeg)
				throw std::runtime_error("Identical segs detected");
			if (res)
			{
				cout << "Effective" << endl;
				cout << prevSeg << endl;
				cout << nextSeg << endl;
				break;
			}
			tr.remove(s);
			Node* n = tr.search(tr.getRoot(), s, p.x);
			if (n)
				throw std::runtime_error("Node found after removal");
		}
	}
	return res;
}

void VecSeg::read(const string& filePath)
{
	ifstream file;
	file.open(filePath);
	string res;
	if (file.is_open())
	{
		while (getline(file, res))
		{
			vector<float> coord;
			string elem;
			stringstream elemInLine(res);
			while (getline(elemInLine, elem, ' '))
				coord.push_back(stof(elem));
			Segment seg_(Point(coord[0], coord[1]), Point(coord[2], coord[3]));
			pushback(seg_);
			//segs.push_back(seg_);
			//points.push_back(Point(coord[0], coord[1]));
			//points.push_back(Point(coord[2], coord[3]));
		}
		file.close();
	}
}

void VecSeg::write(const string& filePath, bool clearFile)
{
	if (filePath == "")
		throw - 1;
	ofstream file;
	if (clearFile)
		file.open(filePath);
	else
		file.open(filePath, ios::app);
	if (file.is_open())
	{
		for (auto& elem : segs)
			file << elem << endl;
		//file << "-==-" << endl;
		file.close();
	}
	else
		exit(-1);
}

istream& operator>>(istream& is, VecSeg& vSeg)
{
	int size;
	cout << "Size: ";
	cin >> size;
	Segment seg;
	for (int i = 0; i < size; i++)
	{
		is >> seg;
		vSeg.pushback(seg);
		//cout << "i = " << i << endl;
		//is >> vSeg.segs[i];
		//vSeg.points[i] = vSeg.segs[i].getBegin();
		//vSeg.points[i + 1] = vSeg.segs[i].getEnd();
	}
	return is;
}

ostream& operator<<(ostream& os, VecSeg& vSeg)
{
	for (auto i = 0; i < vSeg.segs.size(); i++)
		os << vSeg.segs[i] << endl;
	return os;
}

/*VecSeg& VecSeg::operator=(const VecSeg& vs)
{
	for (int i = 0; i < segs.size(); i++)
	{

	}
}*/

/*Tree tree;
bool inter = false;

int count = 0;
for (auto p : points) {
	count++;
	Segment s;
	s = segs[p.segIndex];

	if (s.getBegin().x == s.getEnd().x) throw - 1;

	if (p.isLeft) {
		tree.insert(tree.getRoot(), s);
		Node* addedSegment = tree.search(tree.getRoot(), s, s.getBegin().x);
		Segment s1 = tree.getPrev(addedSegment);
		inter = intersection(s, s1);
		if (s == s1) throw - 1;
		else
			cout << "ezsrxdcgfhjnkmk\n";
		if (inter) {
			std::cout << s << std::endl;
			std::cout << s1 << std::endl;
			break;
		}
		Segment s2 = tree.getNext(addedSegment);
		inter = intersection(s, s2);
		if (s == s2) throw - 1;
		else
			cout << "ezsrxdcgfhjnkmk\n";
		if (inter) {
			std::cout << s << std::endl;
			std::cout << s2 << std::endl;
			break;
		}
	}
	else {
		Node* node = tree.search(tree.getRoot(), s, p.x);
		if (!node) {
			node = tree.search(tree.getRoot(), s, p.x);
		}
		if (s != node->seg) throw - 1;
		else
			cout << "ezsrxdcgfhjnkmk\n";
		Segment s1 = tree.getPrev(node);
		Segment s2 = tree.getNext(node);
		inter = intersection(s1, s2);
		if (s1 == s2) throw - 1;
		else
			cout << "ezsrxdcgfhjnkmk\n";
		if (inter) {
			std::cout << s1 << std::endl;
			std::cout << s2 << std::endl;
			break;
		}
		tree.remove(s);
		Node* n = tree.search(tree.getRoot(), s, p.x);
		if (n) throw - 1;
	}
}
std::cout << (count == points.size()) << std::endl;
return inter;*/