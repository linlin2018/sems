/*
 * Interface header file.
 *
 * Generated by SIP 4.5.2 (4.5.2) on Tue Oct 16 13:58:18 2007
 */

#ifndef _py_sems_libPySemsB2ABCalleeDialog_h
#define _py_sems_libPySemsB2ABCalleeDialog_h

#line 82 "PySemsB2ABDialog.sip"
#include "../PySemsB2ABDialog.h"
#include "../../../core/AmB2ABSession.h"
#line 14 "sippy_sems_libPySemsB2ABCalleeDialog.h"

#define sipClass_PySemsB2ABCalleeDialog             sipModuleAPI_py_sems_lib.em_types[2]
#define sipCast_PySemsB2ABCalleeDialog              sipType_py_sems_lib_PySemsB2ABCalleeDialog.td_cast
#define sipForceConvertTo_PySemsB2ABCalleeDialog    sipType_py_sems_lib_PySemsB2ABCalleeDialog.td_fcto

extern sipTypeDef sipType_py_sems_lib_PySemsB2ABCalleeDialog;


class sipPySemsB2ABCalleeDialog : public PySemsB2ABCalleeDialog
{
public:
    sipPySemsB2ABCalleeDialog(const string&);
    virtual ~sipPySemsB2ABCalleeDialog();

    /*
     * There is a public method for every protected method visible from
     * this class.
     */
    void sipProtectVirt_onPyB2ABEvent(bool,PySemsB2ABEvent *);

    /*
     * There is a protected method for every virtual method visible from
     * this class.
     */
protected:
    void onPyB2ABEvent(PySemsB2ABEvent *);

public:
    sipWrapper *sipPySelf;

private:
    sipPySemsB2ABCalleeDialog(const sipPySemsB2ABCalleeDialog &);
    sipPySemsB2ABCalleeDialog &operator = (const sipPySemsB2ABCalleeDialog &);

    sipMethodCache sipPyMethods[1];
};

#endif