#pragma once
#include "User.h"
#include "Object.h"
#include "Info.h"
#include "Legend.h"

class Object;

class CHayeonsuDoc : public CDocument
{
	CHayeonsuDoc();
	virtual ~CHayeonsuDoc();

public:
	User   user;
	Object object;
	Info   info;
	Legend legend1, legend2, legend3;
	//Legend pikachu, pairi, kkobugi, isanghaessi;
	DECLARE_DYNCREATE(CHayeonsuDoc)

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif

	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	void SetSearchContent(const CString& value);
#endif
};
