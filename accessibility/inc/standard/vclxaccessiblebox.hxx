/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_ACCESSIBILITY_INC_STANDARD_VCLXACCESSIBLEBOX_HXX
#define INCLUDED_ACCESSIBILITY_INC_STANDARD_VCLXACCESSIBLEBOX_HXX

#include <map>
#include <standard/vclxaccessibleedit.hxx>
#include <com/sun/star/accessibility/AccessibleRole.hpp>
#include <com/sun/star/accessibility/XAccessibleKeyBinding.hpp>
#include <com/sun/star/accessibility/XAccessibleValue.hpp>
#include <cppuhelper/implbase3.hxx>


typedef ::cppu::ImplHelper3<
    css::accessibility::XAccessible,
    css::accessibility::XAccessibleValue,
    css::accessibility::XAccessibleAction
    > VCLXAccessibleBox_BASE;


/** Base class for list- and combo boxes.  This class manages the box'
    children.  The classed derived from this one have only to implement the
    IsValid method and return the correct implementation name.
*/
class VCLXAccessibleBox
    : public VCLXAccessibleComponent,
      public VCLXAccessibleBox_BASE
{
public:
    enum BoxType {COMBOBOX, LISTBOX};

    /** The constructor is initialized with the box type which may be
        either COMBOBOX or LISTBOX and a flag
        indicating whether the box is a drop down box.
    */
    VCLXAccessibleBox (VCLXWindow* pVCLXindow, BoxType aType, bool bIsDropDownBox);

    // XTypeProvider
    DECLARE_XTYPEPROVIDER()

    // XInterface
    DECLARE_XINTERFACE()


    // XAccessible

    virtual css::uno::Reference< css::accessibility::XAccessibleContext > SAL_CALL
            getAccessibleContext(  ) override;

    // XAccessibleContext

    /** Each object has one or two children: an optional text field and the
        actual list.  The text field is not provided for non drop down list
        boxes.
    */
    sal_Int32 SAL_CALL getAccessibleChildCount() override;
    /** For drop down list boxes the text field is a not editable
        VCLXAccessibleTextField, for combo boxes it is an
        editable VLCAccessibleEdit.
    */
    css::uno::Reference< css::accessibility::XAccessible> SAL_CALL
        getAccessibleChild (sal_Int32 i) override;
    /** The role is always AccessibleRole::COMBO_BOX.
    */
    sal_Int16 SAL_CALL getAccessibleRole() override;

    sal_Int32 SAL_CALL getAccessibleIndexInParent() override;

    // XAccessibleAction

    /** There is one action for drop down boxes and none for others.
    */
    virtual sal_Int32 SAL_CALL getAccessibleActionCount() override;
    /** The action for drop down boxes lets the user toggle the visibility of the
        popup menu.
    */
    virtual sal_Bool SAL_CALL doAccessibleAction (sal_Int32 nIndex) override;
    /** The returned string is associated with resource
        RID_STR_ACC_ACTION_TOGGLEPOPUP.
    */
    virtual OUString SAL_CALL getAccessibleActionDescription (sal_Int32 nIndex) override;
    /** No keybinding returned so far.
    */
    virtual css::uno::Reference< css::accessibility::XAccessibleKeyBinding > SAL_CALL
            getAccessibleActionKeyBinding( sal_Int32 nIndex ) override;

    // XAccessibleValue

    virtual css::uno::Any SAL_CALL getCurrentValue( ) override;

    virtual sal_Bool SAL_CALL setCurrentValue(
        const css::uno::Any& aNumber ) override;

    virtual css::uno::Any SAL_CALL getMaximumValue(  ) override;

    virtual css::uno::Any SAL_CALL getMinimumValue(  ) override;
protected:
    /** Specifies whether the box is a combo box or a list box.  List boxes
        have multi selection.
    */
    BoxType m_aBoxType;

    /// Specifies whether the box is a drop down box and thus has an action.
    bool m_bIsDropDownBox;

    /// The child that represents the text field if there is one.
    css::uno::Reference< css::accessibility::XAccessible>
        m_xText;

    /// The child that contains the items of this box.
    css::uno::Reference< css::accessibility::XAccessible>
        m_xList;

    /** This flag specifies whether an object has a text field as child
        regardless of whether that child being currently instantiated or
        not.
    */
    bool m_bHasTextChild;

    /** This flag specifies whether an object has a list as child regardless
        of whether that child being currently instantiated or not.  This
        flag is always true in the current implementation because the list
        child is just another wrapper around this object and thus has the
        same life time.
    */
    bool m_bHasListChild;

    virtual ~VCLXAccessibleBox() override;

    /** Returns true when the object is valid.
    */
    virtual bool IsValid() const = 0;

    virtual void ProcessWindowChildEvent (const VclWindowEvent& rVclWindowEvent) override;
    virtual void ProcessWindowEvent (const VclWindowEvent& rVclWindowEvent) override;

    virtual void FillAccessibleStateSet( utl::AccessibleStateSetHelper& rStateSet ) override;

private:
    /// Index in parent.  This is settable from the outside.
    sal_Int32 m_nIndexInParent;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
