#pragma once

#include <QLineEdit>
#include <QWidget>

namespace checo::rimworld
{

class ImageToPlanWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit ImageToPlanWidget(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~ImageToPlanWidget();

  public slots:
    void selectImage();
    void selectPlan();

    void convert();

  private:
    QLineEdit *m_EdtImagePath{nullptr};
    QLineEdit *m_EdtPlanPath{nullptr};
};

} // namespace checo::rimworld
