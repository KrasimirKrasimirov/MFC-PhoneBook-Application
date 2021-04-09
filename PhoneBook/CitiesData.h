#pragma once
#include "CitiesTable.h"
class CCitiesData
{
	// Constructor / Destructor
	// ----------------
public:
	CCitiesData();
	~CCitiesData();
	// Methods
	// ----------------
	BOOL SelectAll(CCitiesArray & oCitiesArray);
	BOOL SelectWhereID(const long lID, CITIES & recCities);
	BOOL Insert(CITIES & recCities);
	BOOL UpdateWhereID(const long lID, const CITIES & recCities);
	BOOL DeleteWhereID(const long lID);


	// Members
	// ----------------
	CCitiesTable m_oCitiesTable;
};