#include "checo/command_executor/start_application.h"

#include <QDesktopServices>
#include <QUrl>

namespace checo::command_executor
{

StartAppCommandExecutor::StartAppCommandExecutor(const checo::os::ApplicationInfo &appInfo) : mAppInfo{appInfo}
{
}

const checo::os::ApplicationInfo &StartAppCommandExecutor::applicationInfo() const
{
    return mAppInfo;
}

void StartAppCommandExecutor::execute()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(mAppInfo.executable().absoluteFilePath()));
}

QByteArray StartAppCommandExecutor::toByteArray() const
{
    return mAppInfo.toByteArray();
}

void StartAppCommandExecutor::fromByteArray(const QByteArray &data)
{
    mAppInfo.fromByteArray(data);
}

QString StartAppCommandExecutor::toString()
{
    return QObject::tr("Launch \"%1\"").arg(mAppInfo.displayName());
}

} // namespace checo::command_executor
