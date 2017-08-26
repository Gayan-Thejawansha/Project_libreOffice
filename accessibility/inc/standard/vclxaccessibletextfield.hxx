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

#ifndef INCLUDED_ACCESSIBILITY_INC_STANDARD_VCLXACCESSIBLETEXTFIELD_HXX
#define INCLUDED_ACCESSIBILITY_INC_STANDARD_VCLXACCESSIBLETEXTFIELD_HXX

#include <standard/vclxaccessibletextcomponent.hxx>

#include <cppuhelper/implbase1.hxx>

typedef ::cppu::ImplHelper1< css::accessibility::XAccessible > VCLXAccessible_BASE;


/** This class represents non editable text fields.  The object passed to
    the constructor is expected to be a list (a ListBox to be
    more specific).  From this always the selected item is token to be made
    accessible by this class.  When the selected item changes then also the
    exported text changes.
*/
class VCLXAccessibleTextField :
    public VCLXAccessibleTextComponent,
    public VCLXAccessible_BASE
{
public:
    VCLXAccessibleTextField (VCLXWindow* pVCLXindow,
                             const css::uno::Reference< css::accessibility::XAccessible >& _xParent);

    // XInterface
    DECLARE_XINTERFACE()

    // XTypeProvider
    DECLARE_XTYPEPROVIDER()

    // XAccessible
    css::uno::Reference< css::accessibility::XAccessibleContext> SAL_CALL
        getAccessibleContext() override;

    // XAccessibleContext
    sal_Int32 SAL_CALL getAccessibleChildCount() override;
    css::uno::Reference< css::accessibility::XAccessible> SAL_CALL
        getAccessibleChild (sal_Int32 i) override;
    sal_Int16 SAL_CALL getAccessibleRole() override;
    css::uno::Reference< css::accessibility::XAccessible > SAL_CALL
        getAccessibleParent(  ) override;

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName() override;
    // Return text field specific services.
    virtual css::uno::Sequence< OUString > SAL_CALL
        getSupportedServiceNames() override;

protected:
    virtual ~VCLXAccessibleTextField() override;

    /** With this method the text of the currently selected item is made
        available to the VCLXAccessibleTextComponent base class.
    */
    OUString implGetText() override;

private:
    /** We need to save the accessible parent to return it in getAccessibleParent(),
        because this method of the base class returns the wrong parent.
    */
    css::uno::Reference< css::accessibility::XAccessible >  m_xParent;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
