/*
 * Copyright (C) 2011 Aliaksei Stratsilatau <sa@uavos.com>
 *
 * This file is part of the UAV Open System Project
 *  http://www.uavos.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 *
 */
#include "EscReader.h"
//=============================================================================
EscReader::EscReader(QObject *parent)
  : QObject(parent), _escaped()
{}
void EscReader::push(const QByteArray ba)
{
  data.append(ba);
  while(!data.isEmpty()){
    uint cnt=readEscaped();
    if(!cnt)continue;
    emit packet_read(QByteArray((const char*)esc_rx,cnt));
    //qDebug("pkt");
  }
}
//_escaped override
uint EscReader::read(uint8_t *buf,uint sz)
{
  if(data.isEmpty())return 0;
  if((int)sz>data.size())sz=data.size();
  memcpy(buf,data.data(),sz);
  data=data.mid(sz);
  return sz;
}
bool EscReader::write_byte(const uint8_t v)
{
  Q_UNUSED(v);
  return true;
}
void EscReader::escError(void)
{
  //qWarning("ESC reader error");
}
//=============================================================================
