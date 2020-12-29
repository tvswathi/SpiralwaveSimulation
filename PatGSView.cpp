// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PatGSView.cpp : implementation of the CPatGSView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatGS.h"
#endif

#include "PatGSDoc.h"
#include "PatGSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatGSView

IMPLEMENT_DYNCREATE(CPatGSView, CView)

BEGIN_MESSAGE_MAP(CPatGSView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPatGSView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_StartG, &CPatGSView::OnButtonStartg)
	ON_COMMAND(ID_BUTTON_Suspend, &CPatGSView::OnButtonSuspend)
	ON_COMMAND(ID_BUTTON_ResumeG, &CPatGSView::OnButtonResumeg)
END_MESSAGE_MAP()

// CPatGSView construction/destruction

CPatGSView::CPatGSView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread=NULL;
	m_iCounter=0;

}

CPatGSView::~CPatGSView()
{
}

BOOL CPatGSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPatGSView drawing

void CPatGSView::OnDraw(CDC* pDC)
{
	CPatGSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString strCounter;
	strCounter.Format(L"The Counter is %d", m_iCounter);
	/*if (m_iCounter > 0)
	{
		pDC->TextOut(100, 100, strCounter);
	}*/

	for (int i = 0; i < m_PointArray.GetSize() - 2; i++)
	{
		pDC->MoveTo(m_PointArray[i].x, m_PointArray[i].y);
		pDC->LineTo(m_PointArray[i + 1].x, m_PointArray[i + 1].y);

	}
	


	// TODO: add draw code for native data here
}


// CPatGSView printing


void CPatGSView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPatGSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatGSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatGSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPatGSView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPatGSView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPatGSView diagnostics

#ifdef _DEBUG
void CPatGSView::AssertValid() const
{
	CView::AssertValid();
}

void CPatGSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPatGSDoc* CPatGSView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatGSDoc)));
	return (CPatGSDoc*)m_pDocument;
}
#endif //_DEBUG


// CPatGSView message handlers


void CPatGSView::OnButtonStartg()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("Start"));
	m_pCurrentThread=AfxBeginThread(CPatGSView::StartThread, this);
}


void CPatGSView::OnButtonSuspend()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("Suspend"));
	m_pCurrentThread->SuspendThread();
}


void CPatGSView::OnButtonResumeg()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("Resume"));
	m_pCurrentThread->ResumeThread();
}


UINT CPatGSView::StartThread(LPVOID Param)
{
	// TODO: Add your implementation code here.
	CPatGSView* pView = (CPatGSView*)Param;
	
	/* while (1)
	{  
		pView-> m_iCounter++;
		pView->Invalidate();
		Sleep(1000);
	}*/
	CPoint MyPoint(200,400);

	while (1)
	{


		//MyPoint.y = 00 + 50 * sin(pView->m_iCounter);
		//MyPoint.x = 100 + pView->m_iCounter;
		
		MyPoint.y = 200 + 100 * sin(pView->m_iCounter);
		MyPoint.x = 200 + 100 * cos(pView->m_iCounter);
		

		pView->m_PointArray.Add(MyPoint);
		pView->m_iCounter = pView->m_iCounter + 5;
		pView->Invalidate();

		Sleep(1000);


	}


	return 0;
}
