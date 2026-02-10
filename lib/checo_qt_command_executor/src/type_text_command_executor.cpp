#include "checo/qt/type_text_command_executor.h"

#include <QObject>

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include <WinUser.h>
#endif // WIN32

namespace checo::qt
{

TypeTextCommandExecutor::TypeTextCommandExecutor() = default;

TypeTextCommandExecutor::TypeTextCommandExecutor(const QString &text)
    : CommandExecutor(),
      m_Text(text)
{
}

TypeTextCommandExecutor::~TypeTextCommandExecutor() = default;

void TypeTextCommandExecutor::execute()
{
#ifdef WIN32
    std::u16string unicodeString = m_Text.toStdU16String();
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
    return m_Text.toUtf8();
}

void TypeTextCommandExecutor::fromByteArray(const QByteArray &data)
{
    m_Text = QString::fromUtf8(data);
}

QString TypeTextCommandExecutor::toString()
{
    int newLineIndex = m_Text.indexOf('\n');
    return QObject::tr("Paste: ") + ((newLineIndex >= 0) ? m_Text.sliced(0, newLineIndex) : m_Text);
}

} // namespace checo::qt
