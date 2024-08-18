#include "checo/command_executor/type_text.h"

#include <QObject>

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include <WinUser.h>
#endif // WIN32

namespace checo::command_executor
{

void TypeTextCommandExecutor::execute()
{
#ifdef WIN32
    std::u16string unicodeString = mText.toStdU16String();
    for (std::u16string::size_type i = 0; i < unicodeString.size(); ++i)
    {
        INPUT curKey;
        curKey.type = INPUT_KEYBOARD;
        curKey.ki.wVk = 0;
        curKey.ki.wScan = static_cast<WORD>(unicodeString[i]);
        curKey.ki.time = 0;
        curKey.ki.dwFlags = KEYEVENTF_UNICODE;
        SendInput(1, &curKey, sizeof(INPUT));

        curKey.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
        SendInput(1, &curKey, sizeof(INPUT));
    }
#endif // WIN32
}

QByteArray TypeTextCommandExecutor::toByteArray() const
{
    return mText.toUtf8();
}

void TypeTextCommandExecutor::fromByteArray(const QByteArray &data)
{
    mText = QString::fromUtf8(data);
}

QString TypeTextCommandExecutor::toString()
{
    int newLineIndex = mText.indexOf('\n');
    return QObject::tr("Paste: ") + ((newLineIndex >= 0) ? mText.sliced(0, newLineIndex) : mText);
}

} // namespace checo::command_executor
