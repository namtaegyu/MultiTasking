﻿
// Multi2View.cpp: CMulti2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Multi2.h"
#endif

#include "Multi2Doc.h"
#include "Multi2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMulti2View

IMPLEMENT_DYNCREATE(CMulti2View, CView)

BEGIN_MESSAGE_MAP(CMulti2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMulti2View::On32771)
	ON_MESSAGE(WM_MAX, OnMaxFound)
END_MESSAGE_MAP()

// CMulti2View 생성/소멸
SData data;
CMulti2View::CMulti2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMulti2View::~CMulti2View()
{
}

BOOL CMulti2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMulti2View 그리기

void CMulti2View::OnDraw(CDC* /*pDC*/)
{
	CMulti2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMulti2View 인쇄

BOOL CMulti2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMulti2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMulti2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMulti2View 진단

#ifdef _DEBUG
void CMulti2View::AssertValid() const
{
	CView::AssertValid();
}

void CMulti2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMulti2Doc* CMulti2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMulti2Doc)));
	return (CMulti2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMulti2View 메시지 처리기
CWinThread* Thread;
UINT ThreadProcedure(LPVOID pParam);
UINT ThreadProcedure(LPVOID pParam) {
	SData* pData = (SData*)pParam;
	//최댓값 찾기
	int i;
	for (i = 0; i < 5; i++) {
		if (pData->array[i] > pData->max)
			pData->max = pData->array[i];
	}
	::PostMessage(pData->NotifiyWindow, WM_MAX, 0, 0);
	return 0;
}
void CMulti2View::On32771()
{
	data.array[0] = 1;
	data.array[0] = 2;
	data.array[0] = 3;
	data.array[0] = 4;
	data.array[0] = 5;
	data.max = data.array[0];
	data.NotifiyWindow = m_hWnd;
	Thread = AfxBeginThread(ThreadProcedure, &data);


	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


LRESULT CMulti2View::OnMaxFound(WPARAM wParam, LPARAM lParam)
{
	CClientDC dc(this);
	CString msg;
	msg.Format(L"%d", data.max);
	dc.TextOut(10,100, msg);
	TerminateThread(Thread, 0);
	return 0;
	// TODO: 여기에 구현 코드 추가.
}
