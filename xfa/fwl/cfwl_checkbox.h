// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef XFA_FWL_CFWL_CHECKBOX_H_
#define XFA_FWL_CFWL_CHECKBOX_H_

#include <memory>

#include "xfa/fwl/cfwl_event.h"
#include "xfa/fwl/cfwl_widget.h"
#include "xfa/fwl/cfwl_widgetproperties.h"

#define FWL_STYLEEXT_CKB_Left (0L << 0)
#define FWL_STYLEEXT_CKB_Center (1L << 0)
#define FWL_STYLEEXT_CKB_Right (2L << 0)
#define FWL_STYLEEXT_CKB_Top (0L << 2)
#define FWL_STYLEEXT_CKB_VCenter (1L << 2)
#define FWL_STYLEEXT_CKB_Bottom (2L << 2)
#define FWL_STYLEEXT_CKB_LeftText (1L << 4)
#define FWL_STYLEEXT_CKB_MultiLine (1L << 5)
#define FWL_STYLEEXT_CKB_3State (1L << 6)
#define FWL_STYLEEXT_CKB_RadioButton (1L << 7)
#define FWL_STYLEEXT_CKB_ShapeSolidSquare (0L << 8)
#define FWL_STYLEEXT_CKB_ShapeSunkenSquare (1L << 8)
#define FWL_STYLEEXT_CKB_ShapeSolidCircle (2L << 8)
#define FWL_STYLEEXT_CKB_ShapeSunkenCircle (3L << 8)
#define FWL_STYLEEXT_CKB_SignShapeCheck (0L << 10)
#define FWL_STYLEEXT_CKB_SignShapeCircle (1L << 10)
#define FWL_STYLEEXT_CKB_SignShapeCross (2L << 10)
#define FWL_STYLEEXT_CKB_SignShapeDiamond (3L << 10)
#define FWL_STYLEEXT_CKB_SignShapeSquare (4L << 10)
#define FWL_STYLEEXT_CKB_SignShapeStar (5L << 10)
#define FWL_STYLEEXT_CKB_HLayoutMask (3L << 0)
#define FWL_STYLEEXT_CKB_VLayoutMask (3L << 2)
#define FWL_STYLEEXT_CKB_ShapeMask (3L << 8)
#define FWL_STYLEEXT_CKB_SignShapeMask (7L << 10)
#define FWL_STATE_CKB_Hovered (1 << FWL_WGTSTATE_MAX)
#define FWL_STATE_CKB_Pressed (1 << (FWL_WGTSTATE_MAX + 1))
#define FWL_STATE_CKB_Unchecked (0 << (FWL_WGTSTATE_MAX + 2))
#define FWL_STATE_CKB_Checked (1 << (FWL_WGTSTATE_MAX + 2))
#define FWL_STATE_CKB_Neutral (2 << (FWL_WGTSTATE_MAX + 2))
#define FWL_STATE_CKB_CheckMask (3L << (FWL_WGTSTATE_MAX + 2))

class CFWL_MessageMouse;
class CFWL_WidgetProperties;
class CFWL_Widget;

class CFWL_CheckBox : public CFWL_Widget {
 public:
  explicit CFWL_CheckBox(const CFWL_App* pApp);
  ~CFWL_CheckBox() override;

  // CFWL_Widget
  FWL_Type GetClassID() const override;
  void Update() override;
  void DrawWidget(CFX_Graphics* pGraphics, const CFX_Matrix* pMatrix) override;

  void OnProcessMessage(CFWL_Message* pMessage) override;
  void OnDrawWidget(CFX_Graphics* pGraphics,
                    const CFX_Matrix* pMatrix) override;

  void SetBoxSize(FX_FLOAT fHeight);

 private:
  void SetCheckState(int32_t iCheck);
  void Layout();
  uint32_t GetPartStates() const;
  void UpdateTextOutStyles();
  void NextStates();
  void OnFocusChanged(bool bSet);
  void OnLButtonDown();
  void OnLButtonUp(CFWL_MessageMouse* pMsg);
  void OnMouseMove(CFWL_MessageMouse* pMsg);
  void OnMouseLeave();
  void OnKeyDown(CFWL_MessageKey* pMsg);

  CFX_RectF m_rtClient;
  CFX_RectF m_rtBox;
  CFX_RectF m_rtCaption;
  CFX_RectF m_rtFocus;
  uint32_t m_dwTTOStyles;
  int32_t m_iTTOAlign;
  bool m_bBtnDown;
  FX_FLOAT m_fBoxHeight;
};

#endif  // XFA_FWL_CFWL_CHECKBOX_H_
