/*  =========================================================================
    fty_srr_helpers - class description

    Copyright (C) 2014 - 2020 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#include "fty_srr_helpers.h"
#include <cxxtools/serializationinfo.h>
#include <fty_common_messagebus.h>

dto::UserData sendRequest(const std::string& action, const dto::UserData& userData)
{
    // conf defaults
    const std::string MLM_END_POINT          = "ipc://@/malamute";
    const std::string AGENT_NAME             = "fty-srr-rest";
    const std::string AGENT_NAME_DESTINATION = "fty-srr-ui";
    const std::string MSG_QUEUE_NAME         = "ETN.Q.IPMCORE.SRR.UI";
    const int         REQUEST_TIMEOUT_SEC    = 10 * 60; // seconds

    int timeout_sec = REQUEST_TIMEOUT_SEC;
    if (action == "list") {
        timeout_sec = 30;
    }

    logDebug("rest_srr sendRequest (action: {}, dest.: {}, queue: {}, timeout: {} sec)",
        action, AGENT_NAME_DESTINATION, MSG_QUEUE_NAME, timeout_sec);

    // Connect client
    std::string                             clientId = messagebus::getClientId(AGENT_NAME);
    std::unique_ptr<messagebus::MessageBus> requester(messagebus::MlmMessageBus(MLM_END_POINT, clientId));
    requester->connect();

    // Build message
    messagebus::Message msg;
    msg.userData() = userData;
    msg.metaData().emplace(messagebus::Message::SUBJECT, action);
    msg.metaData().emplace(messagebus::Message::FROM, clientId);
    msg.metaData().emplace(messagebus::Message::TO, AGENT_NAME_DESTINATION);
    msg.metaData().emplace(messagebus::Message::CORRELATION_ID, messagebus::generateUuid());

    // Send request
    messagebus::Message resp = requester->request(MSG_QUEUE_NAME, msg, timeout_sec);

    logDebug("rest_srr sendRequest (action: {}): response received", action);

    // Return the data response
    return resp.userData();
}

const std::string addSessionToken(const std::string& input, const std::string& sessionToken)
{
    cxxtools::SerializationInfo si = dto::srr::deserializeJson(input);

    if (si.findMember(dto::srr::SESSION_TOKEN) == nullptr) {
        si.addMember(dto::srr::SESSION_TOKEN) <<= sessionToken;
    }

    return dto::srr::serializeJson(si, false);
}
