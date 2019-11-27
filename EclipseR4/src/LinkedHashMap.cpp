/*
 * LinkedHashMap.cpp
 *
 * Linked Hash Map. Creates a HashMap from a linked list of eclipses
 * and Encapsulates the Map and the list in Private Variables, Allowing
 * Mutation and Access of Map through addition, selection and deletion
 * of HashNodes.
 *
 *  Created on: Nov 19, 2017
 *      Author: cglen
 */

#include "LinkedHashMap.h"

/*
 * CONSTRUCTOR:
 * Creates a new linked hash map and sets the size
 * of the map, links the linked list to the hash
 * map, creates a new hash map and syncs the two objects.
 *
 * Author: Clayton Glenn
 */
LinkedHashMap::LinkedHashMap(AVLTree<Eclipse*>* tree) {

	default_list = tree->getList();
	determineSize();
	map = new HashMap<Eclipse*>(mapSize);
	populateMap();
	inSync = true;
	return;
}

/*
 * COPY CONSTRUCTOR:
 * Copies the list, map, and size from another
 * hashtable to this hashtable object.
 *
 * Author: Clayton Glenn
 */
LinkedHashMap::LinkedHashMap(const LinkedHashMap &hashTable) {
	default_list = hashTable.default_list;
	mapSize = hashTable.mapSize;
	map = hashTable.map;
	inSync = hashTable.inSync;
	return;
}

/*
 * DESTRUCTOR:
 * Destroys the hashmap that the linked hash map holds.
 *
 * Author: Clayton Glenn
 */
LinkedHashMap::~LinkedHashMap() {
	map->~HashMap();
	return;
}

/*
 * ADD:
 * This function adds an eclipse to the linked list
 * and hash map simultaneously, so the linked hash
 * map stays in sync.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::add(Eclipse* e) {
	addToList(e);
	addToMap(e);
	inSync = true;
}

/*
 * ADDTOLIST:
 * This function adds an eclipse to the linked list only
 * and the linked hash map is out of sync. Map needs syncopated.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::addToList(Eclipse* e) {
	//Add eclipse to LinkedList
	if (default_list->count() != 0) {
		int i = 1;
		while (i < default_list->count()) {
			if (e->getCatNum() < default_list->peek(i)->getCatNum()) {
				break;
			}
			i++;
		}
		default_list->add_after(e, i);
	} else {
		default_list->create_list(e);
	}
	inSync = false;
	return;
}

/*
 * ADDTOMAP:
 * This function adds an eclipse to the HashMap only
 * and the linked hash map is out of sync. List needs syncopated.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::addToMap(Eclipse* e) {
	map->insert(e->getCatNum(), e);
	inSync = false;
	return;
}

/*
 * REMOVE:
 * This function removes an eclipse from the linked list
 * and hash map simultaneously, so the linked hash
 * map stays in sync.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::remove(int key) {
	removeFromList(key);
	removeFromMap(key);
	inSync = true;
	return;
}

/*
 * REMOVEFROMLIST:
 * This function removes an eclipse from the linked list only
 * and the linked hash map is out of sync. Map needs syncopated.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::removeFromList(int key) {
	int i = 0;
	Eclipse* n = new Eclipse("", i);
	Eclipse* e = get(key);
	if (e->getCatNum() != n->getCatNum()) {
		try{
			default_list->delete_object(e);
		} catch (invalid_argument& except){

		}
	}
	inSync = false;
	return;
}

/*
 * REMOVEFROMMAP:
 * This function removes an eclipse from the Hash Map only
 * and the linked hash map is out of sync. List needs syncopated.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::removeFromMap(int key) {
	map->remove(key);
	inSync = false;
	return;
}

/*
 * GET:
 * This function gets a certain object from the
 * hashmap and returns it to the calling function.
 *
 * Author: Clayton Glenn
 */
Eclipse* LinkedHashMap::get(int key) const {
	try {
		return map->get(key);
	} catch (invalid_argument &excpt) {
		int i = 0;
		Eclipse *e = new Eclipse("", i);
		return e;
	}
}

/*
 * GETMAPSIZE:
 * This function returns the size of the hash map only.
 *
 * Author: Clayton Glenn
 */
int LinkedHashMap::getMapSize() const {
	return mapSize;
}

/*
 * GETLISTSIZE:
 * This function returns the size of the linked list only.
 *
 * Author: Clayton Glenn
 */
int LinkedHashMap::getListSize() const {
	return default_list->count();
}

/*
 * PRINTLIST:
 * This function prints the default_list of the linked hash map.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::printList(ostream &o) {
	o << default_list << endl;
	return;
}

/*
 * PRINTMAP:
 * This function prints the Hash Map of the linked hash map.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::printMap(ostream &o) {
	o << map << endl;
	return;
}

/*
 * SYNC:
 * This function returns true if the linked hash
 * map is syncopated and false if the list isn't.
 *
 * Author: Clayton Glenn
 */
bool LinkedHashMap::sync() const {
	return inSync;
}

/*
 * ISEMPTY:
 * This function returns true if the linked list
 *  is empty and false if the list isn't.
 *
 * Author: Clayton Glenn
 */
bool LinkedHashMap::isEmpty() const {
	if (default_list->count() == 0) {
		return true;
	}
	return false;
}

/*
 * DETERMINESIZE:
 * This function is private and determines the size
 * of the hash map by the size of the linked list it
 * is integrated with.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::determineSize() {
	mapSize = default_list->count() + default_list->count() / 2;
	return;
}

/*
 * POPULATEMAP:
 * This function is private and populates the hash map
 * with all of the objects that are in the linked list.
 *
 * Author: Clayton Glenn
 */
void LinkedHashMap::populateMap() {
	Eclipse* e;
	for (int i = 1; i <= default_list->count(); ++i) {
		e = default_list->peek(i);
		map->insert(e->getCatNum(), e);
	}
	return;
}

