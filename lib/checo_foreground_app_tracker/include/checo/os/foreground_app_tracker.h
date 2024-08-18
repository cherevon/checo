#pragma once

#include "checo_foreground_app_tracker_export.h"

#include <QObject>

namespace checo::os
{

/// Class that provides information window of which application is currently foreground
class CHECO_FOREGROUND_APP_TRACKER_EXPORT ForegroundAppTracker : public QObject
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

} // namespace checo::os
