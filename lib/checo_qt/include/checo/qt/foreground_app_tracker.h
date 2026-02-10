#pragma once

#include "checo_qt_export.h"

#include <QObject>

namespace checo::qt
{

/// Class that provides information window of which application is currently foreground
class CHECO_QT_EXPORT ForegroundAppTracker : public QObject
{
    Q_OBJECT

  public:
    explicit ForegroundAppTracker(QObject *parent = nullptr);
    ~ForegroundAppTracker() override;

  public:
    QString foregroundApplication() const;

  signals:
    void foregroundApplicationChanged();
};

} // namespace checo::qt
