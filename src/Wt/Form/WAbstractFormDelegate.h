// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2021 Emweb bv, Herent, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef WT_FORM_ABSTRACT_FORM_DELEGATE_H_
#define WT_FORM_ABSTRACT_FORM_DELEGATE_H_

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

/*! \defgroup form Dbo Forms (Wt::Form)
 *  \brief Classes that handle the Dbo Forms.
 *
 * This module allows %Wt to automatically generate a form for a Dbo class.
 * Based on the data types that are used within the Dbo class, %Wt will generate form delegates.
 * These form delegates are responsible for creating the widget, creating an optional validator,
 * and making sure that the data is correctly loaded in and from the model.
 * For example: WString objects are by default represented by a WLineEdit, WDate objects by WDateEdit
 * and so on.
 *
 * The user is able to override the default behavior one of three ways:
 * 1. By customizing the widget and/or validator generated by %Wt
 *    \sa Wt::Form::Dbo::FormView<C>::customizeFormWidget, Wt::Form::Dbo::FormView<C>::customizeValidator
 * 2. By creating a new form delegate for a specific field and adding it to the view
 *    \sa Wt::Form::Dbo::FormView<C>::setFormDelegate
 * 3. By specializing a form delegate for a specific type (like an enum)
 *    \sa Wt::Form::WAbstractFormDelegate
 */

namespace Wt {
  /*! \brief Namespace for the \ref form
   */
  namespace Form {

/*! \class WAbstractFormDelegate Wt/Form/WAbstractFormDelegate.h Wt/Form/WAbstractFormDelegate.h
 *  \brief Abstract delegate class for creating form widgets
 *
 * %Form delegates will be automatically generated using Wt::Dbo's persist method.
 * Depending on the data type used by the %Dbo class, the form delegate will
 * have a different behavior. For example: for WString objects the default widget
 * in the view will be a WLineEdit.
 *
 * %Form delegates will be automatically generated when calling Dbo::FormView<C>::setFormModel().
 * This FormView also has the option to override the delegates that are generated by
 * using Dbo::FormView<C>::setFormDelegate().
 *
 * %Form delegates will also create the corresponding WValidator and update
 * the WFormModel and WTemplateFormView accordingly.
 *
 * \ingroup form
 */
class WT_API WAbstractFormDelegate
{
public:
  /*! \brief Create the widget to be used in the View
   */
  virtual std::unique_ptr<Wt::WWidget> createFormWidget() = 0;

  /*! \brief Create the validator to be used by the Model
   *
   * By default this returns a null pointer. When specializing this class,
   * the user needs to override this method if they want to add validation
   * to this field.
   */
  virtual std::shared_ptr<Wt::WValidator> createValidator();

  /*! \brief Updates a value in the Model
   *
   * By default this sets the value in the model to the string returned by WFormWidget::valueText
   *
   * The user should only override this method or the other updateModelValue
   * method returning a boolean, depending on the type of widget that's returned
   * by createFormWidget.
   *
   * \sa WTemplateFormView::updateModelValue()
   */
  virtual void updateModelValue(Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WFormWidget *edit);

  /*! \brief Updates a value in the Model
   *
   * By default this method returns false.
   *
   * The user should only override this method or the other updateModelValue
   * method, depending on the type of widget that's returned by createFormWidget.
   *
   * \sa WTemplateFormView::updateModelValue()
   */
  virtual bool updateModelValue(Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WWidget *edit);

  /*! \brief Updates a value in the View
   *
   * By default this uses WFormWidget::setValueText and WFormModel::value to update the widget
   *
   * The user should only override this method or the other updateViewValue method returning
   * a boolean, depending on the type of widget that's returned by createFormWidget.
   *
   * \sa WTemplateFormView::updateViewValue()
   */
  virtual void updateViewValue(Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WFormWidget *edit);

  /*! \brief Updates a value in the View
   *
   * By default this method returns false.
   *
   * The user should only override this method or the other updateViewValue method, depending on
   * the type of widget that's returned by createFormWidget.
   *
   * \sa WTemplateFormView::updateViewValue()
   */
  virtual bool updateViewValue(Wt::WFormModel *model, Wt::WFormModel::Field field, Wt::WWidget *edit);
};
  }
}

#endif // WT_FORM_ABSTRACT_FORM_DELEGATE
