#pragma once

class TabPage
{
public:
  virtual ~TabPage() {}
  virtual CDialog *       GetDialog() = 0;

  // Whether the application can leave this page
  virtual bool            CanExit(bool bLeaveApplication) { (void)bLeaveApplication; return true; }
};
