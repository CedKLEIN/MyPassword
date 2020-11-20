#pragma once

struct IListener{
    virtual ~IListener()=default;
    virtual void onEventClose()=0;
};
