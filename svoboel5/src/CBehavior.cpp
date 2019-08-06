#include "CBehavior.h"

#include <cstdlib>
#include <algorithm>
#include <list>
#include <utility>
#include <iostream>
#include <fstream>
#include <set>

CBehavior::CBehavior()
{
	srand(time(0));
}

CBehavior::CBehavior(const CBehavior & src)
{}

CBehavior::~CBehavior()
{}

// bfs
list<pair<size_t, size_t>> CBehavior::AtoB(CMap * map, size_t from_x, size_t from_y, size_t to_x, size_t to_y)
{
	vector<vector<bool>> visited;
	vector<vector<CTile *>> ancestor;
	vector<bool> tmp;
	vector<CTile *> tmp_a;

	for(size_t i = 0; i < map->getHeight(); ++i){
		for(size_t j = 0; j < map->getWidth(); ++j){
			tmp.push_back(false);
			tmp_a.push_back(NULL);
		}
		visited.push_back(tmp);
		ancestor.push_back(tmp_a);
		tmp.clear();
		tmp_a.clear();
	}

	list<CTile *> queue;
	queue.push_back(map->getElement(from_x, from_y));
	visited.at(from_y).at(from_x) = true;

	CTile * scaned;
	list<CTile *> list;
	size_t x, y;

	while(!queue.empty()){
		scaned = queue.front();
		x = scaned->getX();
		y = scaned->getY();
		list = map->getElement(x, y)->getListOfNeighbours();
		queue.pop_front();
		for(auto i : list){
			if((visited.at(i->getY()).at(i->getX())) == false){
				visited.at(i->getY()).at(i->getX()) = true;
				ancestor.at(i->getY()).at(i->getX()) = scaned;
				queue.push_back(i);
				if(i->getX() == to_x && i->getY() == to_y){
					return makeList(ancestor, to_x, to_y);
				}
			}
		}
	}
	// not found
	std::list<std::pair<size_t, size_t>> not_found;
	return not_found;
}

list<pair<size_t, size_t>> CBehavior::makeList(vector<vector<CTile *>> ancestor, size_t x, size_t y)
{
	list<pair<size_t, size_t>> route;
	size_t tmp_x;
	while(ancestor.at(y).at(x)){
		route.push_front(make_pair(ancestor.at(y).at(x)->getX(), ancestor.at(y).at(x)->getY()));
		tmp_x = x;
		x = ancestor.at(y).at(x)->getX();
		y = ancestor.at(y).at(tmp_x)->getY();
	}

	return route;
}

pair<size_t, size_t> CBehavior::pickRandomPlace(CMap * map)
{
	int rand_x = rand() % map->getWidth();
	int rand_y = rand() % map->getHeight();

	while(!map->freeToGo(rand_x, rand_y)){
		rand_x = rand() % map->getWidth();
		rand_y = rand() % map->getHeight();
	}

	return make_pair(rand_x, rand_y);
}

map<pair<size_t, size_t>, pair<size_t, size_t>> CBehavior::smallestCycle(CMap * map, size_t start_x, size_t start_y)
{
	vector<vector<bool>> visited;
	vector<vector<CTile *>> ancestor;
	vector<bool> tmp;
	vector<CTile *> tmp_a;

	for(size_t i = 0; i < map->getHeight(); ++i){
		for(size_t j = 0; j < map->getWidth(); ++j){
			tmp.push_back(false);
			tmp_a.push_back(NULL);
		}
		visited.push_back(tmp);
		ancestor.push_back(tmp_a);
		tmp.clear();
		tmp_a.clear();
	}

	list<CTile *> queue;
	queue.push_back(map->getElement(start_x, start_y));
	visited.at(start_y).at(start_x) = true;

	CTile * scaned;
	list<CTile *> list;
	size_t x, y;

	while(!queue.empty()){
		scaned = queue.front();
		x = scaned->getX();
		y = scaned->getY();
		list = map->getElement(x, y)->getListOfNeighbours();
		queue.pop_front();
		for(auto i : list){
			for(auto j : queue){
				if(i->getX() == j->getX() && i->getY() == j->getY())
					return makeMap(ancestor, j->getX(), j->getY(), x, y);
			}
			if((visited.at(i->getY()).at(i->getX())) == false){
				visited.at(i->getY()).at(i->getX()) = true;
				ancestor.at(i->getY()).at(i->getX()) = scaned;
				queue.push_back(i);
			}
		}
	}
	// not found
	std::map<pair<size_t, size_t>, pair<size_t, size_t>> not_found;
	return not_found;
}

// makes cyclic map
map<pair<size_t, size_t>, pair<size_t, size_t>> CBehavior::makeMap(vector<vector<CTile *>> ancestor, size_t x, size_t y, size_t x2, size_t y2)
{
	map<pair<size_t, size_t>, pair<size_t, size_t>>	route;
	size_t x_where, y_where, tmp_x, tmp_y;

	x_where = x;
	y_where = y;

	while(ancestor.at(y).at(x) != NULL){
		route.insert(make_pair(make_pair(x, y), make_pair(ancestor.at(y).at(x)->getX(), ancestor.at(y).at(x)->getY())));
		tmp_x = x;
		x = ancestor.at(y).at(x)->getX();
		y = ancestor.at(y).at(tmp_x)->getY();
	}
	while(ancestor.at(y2).at(x2) != NULL){
		route.insert(make_pair(make_pair(x2, y2), make_pair(x_where, y_where)));
		tmp_x = ancestor.at(y2).at(x2)->getX();
		tmp_y = ancestor.at(y2).at(x2)->getY();
		x_where = x2;
		y_where = y2;
		x2 = tmp_x;
		y2 = tmp_y;
	}

	route.insert(make_pair(make_pair(x2, y2), make_pair(x_where, y_where)));

	return route;
}

void CBehavior::changeRoute(CMap * map, CEntity * prey, size_t from_x, size_t from_y)
{}