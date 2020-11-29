#pragma once

struct IUpdateIconThemeListener{
    virtual ~IUpdateIconThemeListener()=default;
    virtual void onEventUpdateIconTheme()=0;
};
