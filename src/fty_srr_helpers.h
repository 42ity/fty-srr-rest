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

#pragma once

#include <string>
#include <fty_srr_dto.h>

/// Send a request and wait reply in synchronous mode.
/// @param action Request action (or subject)
/// @param userData User data to send
/// @return The Reply or MessageBusException when a time out occurs.
dto::UserData sendRequest(const std::string& action, const dto::UserData& userData);

/// Utility to add a session token from an existing payload.
/// @param input string
/// @param sessionToken string
/// @return A json payload with the session token.
const std::string addSessionToken(const std::string& input, const std::string& sessionToken);
