#include "checo/command_executor/key_sequence.h"

#ifdef WIN32
#include <Windows.h>
#endif

#include <QDataStream>

#include <map>

namespace checo::command_executor
{

/// Mapping of Qt keys to virtual codes
static const std::map<Qt::Key, quint32> keyVirtualCodes = {
    {Qt::Key_Backspace, VK_BACK},
    {Qt::Key_Tab, VK_TAB},
    {Qt::Key_Clear, VK_CLEAR},
    {Qt::Key_Return, VK_RETURN},
    {Qt::Key_Enter, VK_RETURN},
    {Qt::Key_Shift, VK_SHIFT},
    {Qt::Key_Control, VK_CONTROL},
    {Qt::Key_Alt, VK_MENU},
    {Qt::Key_Pause, VK_PAUSE},
    {Qt::Key_CapsLock, VK_CAPITAL},
    {Qt::Key_Katakana, VK_HANGUL},
    {Qt::Key_Kanji, VK_KANJI},
    {Qt::Key_Escape, VK_ESCAPE},
    {Qt::Key_Mode_switch, VK_MODECHANGE},
    {Qt::Key_Space, VK_SPACE},
    {Qt::Key_PageUp, VK_PRIOR},
    {Qt::Key_PageDown, VK_NEXT},
    {Qt::Key_End, VK_END},
    {Qt::Key_Home, VK_HOME},
    {Qt::Key_Left, VK_LEFT},
    {Qt::Key_Up, VK_UP},
    {Qt::Key_Right, VK_RIGHT},
    {Qt::Key_Down, VK_DOWN},
    {Qt::Key_Select, VK_SELECT},
    {Qt::Key_Printer, VK_PRINT},
    {Qt::Key_Execute, VK_EXECUTE},
    {Qt::Key_Print, VK_SNAPSHOT},
    {Qt::Key_Insert, VK_INSERT},
    {Qt::Key_Delete, VK_DELETE},
    {Qt::Key_Help, VK_HELP},
    {Qt::Key_Meta, VK_LWIN},
    {Qt::Key_Menu, VK_APPS},
    {Qt::Key_Sleep, VK_SLEEP},
    {Qt::Key_0, VK_NUMPAD0},
    {Qt::Key_1, VK_NUMPAD1},
    {Qt::Key_2, VK_NUMPAD2},
    {Qt::Key_3, VK_NUMPAD3},
    {Qt::Key_4, VK_NUMPAD4},
    {Qt::Key_5, VK_NUMPAD5},
    {Qt::Key_6, VK_NUMPAD6},
    {Qt::Key_7, VK_NUMPAD7},
    {Qt::Key_8, VK_NUMPAD8},
    {Qt::Key_9, VK_NUMPAD9},
    {Qt::Key_Asterisk, VK_MULTIPLY},
    {Qt::Key_Plus, VK_ADD},
    {Qt::Key_Minus, VK_SUBTRACT},
    {Qt::Key_Comma, VK_DECIMAL},
    {Qt::Key_Slash, VK_DIVIDE},
    {Qt::Key_F1, VK_F1},
    {Qt::Key_F2, VK_F2},
    {Qt::Key_F3, VK_F3},
    {Qt::Key_F4, VK_F4},
    {Qt::Key_F5, VK_F5},
    {Qt::Key_F6, VK_F6},
    {Qt::Key_F7, VK_F7},
    {Qt::Key_F8, VK_F8},
    {Qt::Key_F9, VK_F9},
    {Qt::Key_F10, VK_F10},
    {Qt::Key_F11, VK_F11},
    {Qt::Key_F12, VK_F12},
    {Qt::Key_F13, VK_F13},
    {Qt::Key_F14, VK_F14},
    {Qt::Key_F15, VK_F15},
    {Qt::Key_F16, VK_F16},
    {Qt::Key_F17, VK_F17},
    {Qt::Key_F18, VK_F18},
    {Qt::Key_F19, VK_F19},
    {Qt::Key_F20, VK_F20},
    {Qt::Key_F21, VK_F21},
    {Qt::Key_F22, VK_F22},
    {Qt::Key_F23, VK_F23},
    {Qt::Key_F24, VK_F24},
    {Qt::Key_NumLock, VK_NUMLOCK},
    {Qt::Key_ScrollLock, VK_SCROLL},
    {Qt::Key_Massyo, VK_OEM_FJ_MASSHOU},
    {Qt::Key_Touroku, VK_OEM_FJ_TOUROKU},
    {Qt::Key_Shift, VK_LSHIFT},
    {Qt::Key_Control, VK_LCONTROL},
    {Qt::Key_Alt, VK_LMENU},
    {Qt::Key_AltGr, VK_RMENU},
    {Qt::Key_Back, VK_BROWSER_BACK},
    {Qt::Key_Forward, VK_BROWSER_FORWARD},
    {Qt::Key_Refresh, VK_BROWSER_REFRESH},
    {Qt::Key_Stop, VK_BROWSER_STOP},
    {Qt::Key_Search, VK_BROWSER_SEARCH},
    {Qt::Key_Favorites, VK_BROWSER_FAVORITES},
    {Qt::Key_HomePage, VK_BROWSER_HOME},
    {Qt::Key_VolumeMute, VK_VOLUME_MUTE},
    {Qt::Key_VolumeDown, VK_VOLUME_DOWN},
    {Qt::Key_VolumeUp, VK_VOLUME_UP},
    {Qt::Key_MediaNext, VK_MEDIA_NEXT_TRACK},
    {Qt::Key_MediaPrevious, VK_MEDIA_PREV_TRACK},
    {Qt::Key_MediaStop, VK_MEDIA_STOP},
    {Qt::Key_MediaPlay, VK_MEDIA_PLAY_PAUSE},
    {Qt::Key_LaunchMail, VK_LAUNCH_MAIL},
    {Qt::Key_LaunchMedia, VK_LAUNCH_MEDIA_SELECT},
    {Qt::Key_Launch0, VK_LAUNCH_APP1},
    {Qt::Key_Launch1, VK_LAUNCH_APP2},
    {Qt::Key_Excel, VK_EXSEL},
    {Qt::Key_Play, VK_PLAY},
    {Qt::Key_Zoom, VK_ZOOM},
};

quint32 qtKeyToVirtualKeyCode(const Qt::Key key)
{
    if (keyVirtualCodes.count(key) > 0)
        return keyVirtualCodes.at(key);
    else
        return key;
}

void KeySequenceCommandExecutor::execute()
{
#ifdef WIN32
    // Press all keys
    for (const Qt::Key &curKey : mKeySequence)
    {
        keybd_event(qtKeyToVirtualKeyCode(curKey), 0, 0, 0);
    }

    // Release all keys
    for (const Qt::Key &curKey : mKeySequence)
    {
        keybd_event(qtKeyToVirtualKeyCode(curKey), 0, KEYEVENTF_KEYUP, 0);
    }
#endif // WIN32
}

QByteArray KeySequenceCommandExecutor::toByteArray() const
{
    QByteArray result;
    QDataStream streamWrite(&result, QIODeviceBase::WriteOnly);
    for (const Qt::Key &curKey : mKeySequence)
    {
        streamWrite << static_cast<int32_t>(curKey);
    }
    return result;
}

void KeySequenceCommandExecutor::fromByteArray(const QByteArray &data)
{
    mKeySequence.clear();
    QDataStream streamRead(data);
    while (!streamRead.atEnd())
    {
        int32_t keyValue;
        streamRead >> keyValue;
        mKeySequence.push_back(static_cast<Qt::Key>(keyValue));
    }
}

QString KeySequenceCommandExecutor::toString()
{
    QString result;
    for (const auto &curKey : mKeySequence)
    {
        if (!result.isEmpty())
        {
            result += "+";
        }
        if (curKey == Qt::Key_Meta)
        {
            result += "Win";
        }
        else
        {
            result += QKeySequence{curKey}.toString();
        }
    }
    return result;
}

const std::vector<Qt::Key> &KeySequenceCommandExecutor::keySequence() const
{
    return mKeySequence;
}

} // namespace checo::command_executor
