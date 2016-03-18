/**
 * @author Thijs Kruithof, Walter Tamboer
 */

#pragma once

#ifdef WX_GCH
	#include <wx_pch.h>
#else
	#include <wx/wx.h>
#endif

#include <map>
#include <vector>
#include <wx/dcbuffer.h>
#include "Factory.h"
#include "Listener.h"
#include "State.h"
#include "Item.h"

/**
 * The cursors used on the workspace.
 */
enum ECursor
{
	CursorSelect,
	CursorPan,
	CursorMove,
	CursorZoom,
	CursorConnect,
	CursorNormal,
	TotalCursors
};

/**
 * The available interaction states.
 */
enum EInteractionState
{
	InteractionStateNormal,
	InteractionStateSelect,
	InteractionStateConnect,
	InteractionStatePan,
	InteractionStateZoom,
	InteractionStateMove
};

class wxWorkspaceView: public wxControl
{
public:
	wxWorkspaceView(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);
	~wxWorkspaceView();

public:
	void SetAntiAlias(bool Enable);
	void SetBackColor(const wxColor& Color);
	void SetGridColor(const wxColor& Color);

public:
	void SetListener(WorkspaceView::Listener* NewListener);

public:
	void AddItem(WorkspaceView::Item* Item);
	size_t ItemCount();
	void ClearItems();

public:
	void SelectAll();
	void ClearSelection();
	void DeleteSelection();
	void AddToSelection(const wxRect& Area, bool OnlyTopMost);

public:
	WorkspaceView::Item* GetItemFromRectangle(const wxRect& Area) const;
	std::vector<WorkspaceView::Item *> GetItemsFromRectangle(const wxRect& Area) const;

private:
	wxRect NormalizeRectangle(const wxRect& Rect);

private:
	bool HasClickedOnConnector(const wxPoint& ScreenPoint, WorkspaceView::ConnectorInfo* Result);

private:
	void DrawView(wxDC& dc);
	void DrawGrid(wxDC& dc, const wxSize& Size);
	void DrawSelection(wxDC& dc, const wxSize& Size);

private:
	void PaintAntiAliased();
	void PaintAliased();

private:
	std::vector<WorkspaceView::Item*> ItemsArray;

private:
	WorkspaceView::State ViewState;

private:
	wxCursor CursorList[TotalCursors];
	void UpdateCursor();

private:
	EInteractionState InteractionState;
	wxPoint PanningOffsetStart;
	wxPoint InitialMouseDownPosition;

private:
	float ZoomFactorStart;
	float MinimumZoomFactor;
	float MaximumZoomFactor;

private:
	wxRect SelectionRect;
	std::map<WorkspaceView::Item*, wxRect> SelectedItemPositionsOnMoveStart;

private:
	WorkspaceView::Factory* Factory;
	WorkspaceView::Listener* Listener;

public:
	void SetFactory(WorkspaceView::Factory* _factory);

private:
	bool SnapToGrid;
	float GridStep;

private:
	bool AntiAliased;
	wxColor BackColor;
	wxColor GridColor;

private:
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnLeftMouseDown(wxMouseEvent& event);
	void OnLeftMouseUp(wxMouseEvent& event);
	void OnRightMouseDown(wxMouseEvent& event);
	void OnRightMouseUp(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnMouseCaptureLostEvent(wxMouseCaptureLostEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnEraseBackGround(wxEraseEvent& event);

public:
	DECLARE_EVENT_TABLE();
	DECLARE_DYNAMIC_CLASS(wxWorkspaceView);
};