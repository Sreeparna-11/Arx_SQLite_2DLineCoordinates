// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

#include "sqlite-amalgamation-3430100/sqlite3.h"
#include <tchar.h>
using Record = std::vector<std::string>;
using Records = std::vector<Record>;


//-----------------------------------------------------------------------------
#define szRDS _RXST("ADSK")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CArx_SQLite_LineEndPointsInDBApp : public AcRxArxApp {
//code---
public:

	struct LineCoord {
		int x_coord;
		int y_coord;
	};

private:
	static std::vector<LineCoord> m_coordRecords;

//---code---

public:
	CArx_SQLite_LineEndPointsInDBApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the CArx_SQLite_LineEndPointsInDBApp class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, ADSKMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	static void ADSKMyGroupMyCommand () {
		// Put your command code here

	}

	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, ADSKMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void ADSKMyGroupMyPickFirst () {
		ads_name result ;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM )
		{
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else
		{
			// There are no selected entities
			// Put your command code here
		}
	}

	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, ADSKMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void ADSKMyGroupMySessionCmd () {
		// Put your command code here
	}

	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the CArx_SQLite_LineEndPointsInDBApp class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}

	//code---
	static void ADSKMyGroupCreateLineCoord()
	{
		sqlite3* db;
		if (sqlite3_open("LineCoordDB.db", &db) != SQLITE_OK)
		{
			sqlite3_close(db);
			return;
		}

		//store query in string
		std::string createTableQuery = "CREATE TABLE LINECOORD ("
			"ID INT PRIMARY KEY	NOT NULL,"
			"XCOORD INT NOT NULL,"
			"YCOORD INT NOT NULL);";

		//prepare sql statement from the string containing the query
		sqlite3_stmt* createTableStmt;
		sqlite3_prepare(db, createTableQuery.c_str(), static_cast<int>(createTableQuery.size()), &createTableStmt, nullptr);
		
		//execute sql query to create table
		if (sqlite3_step(createTableStmt) != SQLITE_DONE)
		{
			sqlite3_close(db);
		}

		//store INSERT statements into a vector of string
		std::vector<std::string> insertStmtList;
		insertStmtList.emplace_back("INSERT INTO LINECOORD ('ID', 'XCOORD', 'YCOORD') VALUES ('101', '1', '1');");
		insertStmtList.emplace_back("INSERT INTO LINECOORD ('ID', 'XCOORD', 'YCOORD') VALUES ('102', '100', '1');");
		insertStmtList.emplace_back("INSERT INTO LINECOORD ('ID', 'XCOORD', 'YCOORD') VALUES ('103', '100', '100');");

		//prepare sql statements for each INSERT statement stored as a string the vector
		for (const auto& insertQueryStr : insertStmtList)
		{
			sqlite3_stmt* insertStmt;
			sqlite3_prepare(db, insertQueryStr.c_str(), static_cast<int>(insertQueryStr.size()), &insertStmt, nullptr);

			//execute each sql stmt
			if (sqlite3_step(insertStmt) != SQLITE_DONE)
			{
				sqlite3_close(db);
				return;
			}
		}
		sqlite3_close(db);
		return;
	}


	//fetch data
	static void ADSKMyGroupGetLineCoord()
	{
		sqlite3* db;
		if (sqlite3_open("LineCoordDB.db", &db) != SQLITE_OK)
		{
			sqlite3_close(db);
			return;
		}

		//table data fetched in string format 
		Records recs_tableData = exec_select_stmt("SELECT * FROM LINECOORD");
		if (recs_tableData.empty())
			return;

		//fetched data to be stored into table structure format
		m_coordRecords.clear();

		for (const auto& record : recs_tableData)
		{
			if (!record.empty())
			{
				LineCoord var_lineCoord; //struct variable
				var_lineCoord.x_coord = std::atoi(record[1].c_str());
				var_lineCoord.y_coord = std::atoi(record[2].c_str());
				acutPrintf(_T("\n---X: %d | Y: %d\n"), var_lineCoord.x_coord, var_lineCoord.y_coord);
				
				m_coordRecords.emplace_back(var_lineCoord);
			}
		}
		sqlite3_close(db);
	}


	//draw using data
	static void ADSKMyGroupDrawWithLineCoord()
	{
		AcGePoint3d stPt, endPt;
		stPt.x = m_coordRecords[0].x_coord;
		stPt.y = m_coordRecords[0].y_coord;

		endPt.x = m_coordRecords[1].x_coord;
		endPt.y = m_coordRecords[1].y_coord;
		
		//AcGeLine2d line(stPt, endPt);

		//AcGePoint3d startPt(4.0, 2.0, 0.0);
		//AcGePoint3d endPt(10.0, 7.0, 0.0);
		AcDbLine* pLine = new AcDbLine(stPt, endPt);
		AcDbBlockTable* pBlockTable;
		acdbHostApplicationServices()->workingDatabase()
			->getSymbolTable(pBlockTable, AcDb::kForRead);
		AcDbBlockTableRecord* pBlockTableRecord;
		pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord,
			AcDb::kForWrite);
		pBlockTable->close();
		AcDbObjectId lineId;
		pBlockTableRecord->appendAcDbEntity(lineId, pLine);
		pBlockTableRecord->close();
		pLine->close();
	}



	private:

		static int select_callback(void* p_data, int num_fields, char** p_fields, char** p_col_names)
		{
			Records* recsTableData = static_cast<Records*>(p_data);

			try
			{
				recsTableData->emplace_back(p_fields, p_fields + num_fields); //entire table data stored
			}
			catch (...)
			{
				acutPrintf(_T("\nException error while retrieving data from db! Aborting."));
				return 1;
			}
			
			
			/*for (int i = 0; i < num_fields; i++) {
				acutPrintf(_T("%s = %s\n"), p_col_names[i], p_fields[i] ? p_fields[i] : "NULL");
			}*/
			return 0;
		}
		static Records exec_select_stmt(const char* stmt)
		{
			sqlite3* db;
			Records recs_tableData;

			if (sqlite3_open("LineCoordDB.db", &db) != SQLITE_OK)
			{
				sqlite3_close(db);
				return recs_tableData;
			}

			char* errMsg;
			if (sqlite3_exec(db, stmt, select_callback, &recs_tableData, &errMsg) != SQLITE_OK)
			
				acutPrintf(_T("\nError in fetching db results"));
			else
				acutPrintf(_T("\nSuccess in fetching db results"));

			return recs_tableData;
			
		}

		
} ;

std::vector < CArx_SQLite_LineEndPointsInDBApp::LineCoord> CArx_SQLite_LineEndPointsInDBApp::m_coordRecords;   //initialising static data member

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CArx_SQLite_LineEndPointsInDBApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, ADSKMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, ADSKMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, ADSKMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
ACED_ADSSYMBOL_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, MyLispFunction, false)

//code---
ACED_ARXCOMMAND_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, ADSKMyGroup, CreateLineCoord, _CreateLineCoord, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, ADSKMyGroup, GetLineCoord, _GetLineCoord, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArx_SQLite_LineEndPointsInDBApp, ADSKMyGroup, DrawWithLineCoord, _DrawWithLineCoord, ACRX_CMD_MODAL, NULL)
