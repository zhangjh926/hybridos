/*
** HFCL - HybridOS Foundation Class Library
**
** Copyright (C) 2018 Beijing FMSoft Technologies Co., Ltd.
**
** This file is part of HFCL.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#undef _DEBUG

#include "activity/controller.h"

#include "activity/activitymanager.h"
#include "activity/window.h"

#if 0
#include "common/log.h"
#include "view/view.h"
#include "activity/window.h"
#include "appmanager.h"
#include "baseapp.h"
#endif

namespace hfcl {

Controller::Controller(): m_modalCount(0) {
}

Controller::~Controller() {
    cleanAllClients();
}

unsigned int Controller::showView(int view_id, HTData param1, HTData param2)
{
    ControllerClient* client = createClient(view_id, param1, param2);
    if (!client)
        return 1;

    client->setModal(false);

    if(!ActivityManager::getInstance()->actIsExist((BaseActivity *)this))
        return 1;

    _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- create client <%p>", client);

    ControllerClient* top = getTop();

    animationSwitch(top, client);

    //push it into the top
    push(client);
    _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- showView ---- view count : %d", getClientCount());

    if(top) {
        _DBG_PRINTF ("Controller::showView: calling inactive() for %p", top);
        top->inactive();
        _DBG_PRINTF ("Controller::showView: inactive() called for %p", top);
    }
    client->active();

    return 0;
}

void Controller::animationSwitch(ControllerClient* prev, ControllerClient* cur)
{
/*
    IntRect prevRect = prev->getResct();
    IntRect curRect = cur->getRect();
    //TODO
    Point destp = {0, 0};
    Point srcp = {240,0};
    MoveViewAnimation *animation = HFCL_NEW_EX(MoveViewAnimation, (cur, srcp));
    animation->setPoint(destp);
    animation->setDiration(1000);
    animation->setLoopCount(1);
    animation->setKeepLive(false);
    animation->start(true,false);
    animation->wait();
*/
}

unsigned int Controller::switchView(int view_id, HTData param1, HTData param2)
{
    ControllerClient* client = createClient(view_id, param1, param2);
    if(!client)
        return 1;

    client->setModal(false);

    _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- create client <%p>", client);

    ControllerClient* top = getTop();

    animationSwitch(top, client);

    if(top)
        top->inactive();
    client->active();

    setTop(client);

    return 0;
}

unsigned int Controller::showModalView(int view_id,
            HTData param1, HTData param2)
{
    int ret = -1;
    if ((ret = showView(view_id, param1, param2)) == 0) {
        ControllerClient * client = getTop(0);
        RootView* view;

        if(!client || !(view = client->getRootView()))
            return 1;

        m_modalCount ++;
        client->setModal(true);

        return client->getWindow()->doModalView();
    }

    return ret;
}

unsigned int Controller::backView(unsigned int endcode)
{
    ControllerClient* client = getTop(0);
    ControllerClient* underClient = getTop(1);

    if (NULL == underClient) {
        exit();
        return 1;
    }

    animationSwitch(client, underClient);

    if (client) {
        client->onBackView(endcode);
        client->inactive();
    }

    if (m_modalCount > 0) {
        if (client && client->isModal()) {
            client->getWindow()->endDlg(endcode);
            m_modalCount --;
        }
    }

    if (client)
        client->cleanRootView();

    pop(1);

    if (underClient) {
        underClient->onPopView(endcode);
        underClient->active();
    }

    return 0;
}

void Controller::push(ControllerClient* client)
{
    if(!client)
        return ;

    _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- push client <%p>", client);

    m_list.push_front(client);
}

void Controller::moveClientToTop(int view_id)
{
    int i = 0, s = 0;
    ControllerClient* client = NULL;
    ControllerClient* top = getTop(0);

    if(NULL != top && (top->getId() == view_id))
        return;

    s = m_list.size();

    ControllerClientList::iterator it = m_list.begin();

    for(i = 0;i < s; i++, ++it)
    {
        if ((*(it))->getId() == view_id)
        {
            client = *it;

            if(i == 0) //the view id at top
                return;

            //HFCL_DELETE(*it);don't destrory the instance
            i = 0xff;
            break;
        }
    }

    if( client && ( i == 0xff ) )
    {
        _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- remove client <%p>", client);
        m_list.remove(client);

        top = getTop(0);

        push(client);

        if(top)
            top->inactive();
        client->active();
    }
}


int Controller::getTopViewId(void)
{
    ControllerClient* top = getTop(0);

    if(NULL != top)
    {
        return top->getId();
    }
        return -1;
}

ControllerClient* Controller::getTop(int index)
{
    int size = m_list.size();

    if(index < 0 ||index > size)
        return NULL;
    if ((index >= size && size == 1) || (0 == size))
        return NULL;

    if(index >= size)
        index = size - 1;

    ControllerClientList::iterator it;

    for(it = m_list.begin();
            index > 0; index --, ++it);

    if (index == 0 && it == m_list.end())
        return NULL;

    return *it;
}

void Controller::setTop(ControllerClient* client, int index)
{
    if(index <= 0) {
        index = -index;
    } else {
        index = m_list.size() - index;
        if(index < 0)
            return ;
    }

    ControllerClientList::iterator it;
    for (it = m_list.begin(); index > 0; index --, ++it);

    ControllerClient *_clt = *it;
    if (_clt != NULL) {
        _clt->cleanRootView();
        _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- delete client <%p>", _clt);
        HFCL_DELETE(_clt);
        *it = client;
    }
}

void Controller::pop(int pop_count)
{
    if (pop_count <= 0)
        return ;

    ControllerClientList::iterator it = m_list.begin();
    while (pop_count > 0 && it != m_list.end()) {
        ControllerClient *_clt = *it;
        _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- remove client <%p>", _clt);
        ++it;
        m_list.remove(_clt);

        _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- delete client <%p>", _clt);
        HFCL_DELETE(_clt);
        pop_count --;
    }
}

void Controller::cleanAllClients()
{
    // Attention :
    // All the view will be deleted by the view tree (NGUXWindow).
    // So, You needn't delete them here.
    pop (m_list.size());
}

unsigned int Controller::passCommandToClient(int view_id, unsigned int cmd,
        HTData param1, HTData param2)
{
    ControllerClient* client = find(view_id);
    if (!client)
        return 0;

    return client->onControllerCommand(cmd, param1, param2);
}

void Controller::deleteView(int view_id, bool bExit)
{
    ControllerClient* client = find(view_id);

    if (NULL == client)
        return;

    _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- remove client <%p>", client);

    if (m_modalCount > 0) {
        if (client && client->isModal()) {
            client->getWindow()->endDlg(0);
            m_modalCount --;
        }

    }

    m_list.remove(client);

    client->cleanRootView();
    HFCL_DELETE(client);
    _DBG_PRINTF ("HFCL_CONT_TRACE -- controller -- delete client <%p>", client);

    if (bExit && getClientCount() <= 0) {
        exit();
    }
}

ControllerClient* Controller::find(int view_id)
{
    int i = 0;
    int s = m_list.size();

    ControllerClientList::iterator it = m_list.begin();

    for (i = 0; i < s; ++i) {
        if ((*it) != NULL) {
            if ((*(it))->getId() == view_id)
                return *(it);
        }
        ++it;
    }

    return NULL;
}

/////////////////////////////////////////////////////////

void ControllerClient::active()
{
    if (m_rootView) {
        m_rootView->unfreeze();
        m_rootView->focus(); //facusMe
        if (m_currentList)
            m_owner->setMode(m_currentList);
    }
}

void ControllerClient::inactive()
{
    if (m_rootView) {
        // VincentWei: Use freezeUpdate/unfreezeUpdate instead of hide/show.
        // if we hide old one,
        // the transparent view will show wrong when updata
        // if we do NOT hide old one,
        // we will waste a lot to paint all.
        m_rootView->freeze();
    }
    m_inactiveTimes++;
}

ControllerClient::~ControllerClient()
{
    m_owner = NULL; //the controller onwer
    m_id = 0xFFFFFFFF;
    m_modeManager = NULL;
    m_currentList = NULL;
    m_inactiveTimes = 0;
}

int ControllerClient::GetValueFromCurrentMode(int mode_id, int sub_id)
{
    if (!m_modeManager)
        return -1;

    ControllerModeList* modeList = m_modeManager->getModeById(mode_id);
    if (!modeList)
        return -1;

    for (int i=0; i< modeList->mode_count; i++) {
        if (sub_id == modeList->modes[i].id)
            return modeList->modes[i].value;
    }

    return -1;
}

} // namespace hfcl



