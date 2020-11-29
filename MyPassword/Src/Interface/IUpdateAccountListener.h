#pragma once

struct IUpdateAccountListener{
    virtual ~IUpdateAccountListener()=default;
    virtual void onEventUpdateAccount()=0;
};
