
/***************************************************************************
 * dns_request_generation.cc -- Tests DNS request generation               *
 *                                                                         *
 ***********************IMPORTANT NMAP LICENSE TERMS************************
 *                                                                         *
 * The Nmap Security Scanner is (C) 1996-2015 Insecure.Com LLC. Nmap is    *
 * also a registered trademark of Insecure.Com LLC.  This program is free  *
 * software; you may redistribute and/or modify it under the terms of the  *
 * GNU General Public License as published by the Free Software            *
 * Foundation; Version 2 ("GPL"), BUT ONLY WITH ALL OF THE CLARIFICATIONS  *
 * AND EXCEPTIONS DESCRIBED HEREIN.  This guarantees your right to use,    *
 * modify, and redistribute this software under certain conditions.  If    *
 * you wish to embed Nmap technology into proprietary software, we sell    *
 * alternative licenses (contact sales@nmap.com).  Dozens of software      *
 * vendors already license Nmap technology such as host discovery, port    *
 * scanning, OS detection, version detection, and the Nmap Scripting       *
 * Engine.                                                                 *
 *                                                                         *
 * Note that the GPL places important restrictions on "derivative works",  *
 * yet it does not provide a detailed definition of that term.  To avoid   *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * derivative work for the purpose of this license if it does any of the   *
 * following with any software or content covered by this license          *
 * ("Covered Software"):                                                   *
 *                                                                         *
 * o Integrates source code from Covered Software.                         *
 *                                                                         *
 * o Reads or includes copyrighted data files, such as Nmap's nmap-os-db   *
 * or nmap-service-probes.                                                 *
 *                                                                         *
 * o Is designed specifically to execute Covered Software and parse the    *
 * results (as opposed to typical shell or execution-menu apps, which will *
 * execute anything you tell them to).                                     *
 *                                                                         *
 * o Includes Covered Software in a proprietary executable installer.  The *
 * installers produced by InstallShield are an example of this.  Including *
 * Nmap with other software in compressed or archival form does not        *
 * trigger this provision, provided appropriate open source decompression  *
 * or de-archiving software is widely available for no charge.  For the    *
 * purposes of this license, an installer is considered to include Covered *
 * Software even if it actually retrieves a copy of Covered Software from  *
 * another source during runtime (such as by downloading it from the       *
 * Internet).                                                              *
 *                                                                         *
 * o Links (statically or dynamically) to a library which does any of the  *
 * above.                                                                  *
 *                                                                         *
 * o Executes a helper program, module, or script to do any of the above.  *
 *                                                                         *
 * This list is not exclusive, but is meant to clarify our interpretation  *
 * of derived works with some common examples.  Other people may interpret *
 * the plain GPL differently, so we consider this a special exception to   *
 * the GPL that we apply to Covered Software.  Works which meet any of     *
 * these conditions must conform to all of the terms of this license,      *
 * particularly including the GPL Section 3 requirements of providing      *
 * source code and allowing free redistribution of the work as a whole.    *
 *                                                                         *
 * As another special exception to the GPL terms, Insecure.Com LLC grants  *
 * permission to link the code of this program with any version of the     *
 * OpenSSL library which is distributed under a license identical to that  *
 * listed in the included docs/licenses/OpenSSL.txt file, and distribute   *
 * linked combinations including the two.                                  *
 *                                                                         *
 * Any redistribution of Covered Software, including any derived works,    *
 * must obey and carry forward all of the terms of this license, including *
 * obeying all GPL rules and restrictions.  For example, source code of    *
 * the whole work must be provided and free redistribution must be         *
 * allowed.  All GPL references to "this License", are to be treated as    *
 * including the terms and conditions of this license text as well.        *
 *                                                                         *
 * Because this license imposes special exceptions to the GPL, Covered     *
 * Work may not be combined (even as part of a larger work) with plain GPL *
 * software.  The terms, conditions, and exceptions of this license must   *
 * be included as well.  This license is incompatible with some other open *
 * source licenses as well.  In some cases we can relicense portions of    *
 * Nmap or grant special permissions to use it in other open source        *
 * software.  Please contact fyodor@nmap.org with any such requests.       *
 * Similarly, we don't incorporate incompatible open source software into  *
 * Covered Software without special permission from the copyright holders. *
 *                                                                         *
 * If you have any questions about the licensing restrictions on using     *
 * Nmap in other works, are happy to help.  As mentioned above, we also    *
 * offer alternative license to integrate Nmap into proprietary            *
 * applications and appliances.  These contracts have been sold to dozens  *
 * of software vendors, and generally include a perpetual license as well  *
 * as providing for priority support and updates.  They also fund the      *
 * continued development of Nmap.  Please email sales@nmap.com for further *
 * information.                                                            *
 *                                                                         *
 * If you have received a written license agreement or contract for        *
 * Covered Software stating terms other than these, you may choose to use  *
 * and redistribute Covered Software under those terms instead of these.   *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes.          *
 *                                                                         *
 * Source code also allows you to port Nmap to new platforms, fix bugs,    *
 * and add new features.  You are highly encouraged to send your changes   *
 * to the dev@nmap.org mailing list for possible incorporation into the    *
 * main distribution.  By sending these changes to Fyodor or one of the    *
 * Insecure.Org development mailing lists, or checking them into the Nmap  *
 * source code repository, it is understood (unless you specify otherwise) *
 * that you are offering the Nmap Project (Insecure.Com LLC) the           *
 * unlimited, non-exclusive right to reuse, modify, and relicense the      *
 * code.  Nmap will always be available Open Source, but this is important *
 * because the inability to relicense code has caused devastating problems *
 * for other Free Software projects (such as KDE and NASM).  We also       *
 * occasionally relicense the code to third parties as discussed above.    *
 * If you wish to specify special license conditions of your               *
 * contributions, just say so when you send them.                          *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Nmap      *
 * license file for more details (it's in a COPYING file included with     *
 * Nmap, and also available from https://svn.nmap.org/nmap/COPYING)        *
 *                                                                         *
 ***************************************************************************/

#include "../nmap_dns.h"

#include <iostream>

#define TEST_INCR(pred,acc) \
if ( !(pred) ) \
{ \
  std::cout << "Test " << #pred << " failed at " << __FILE__ << ":" << __LINE__ << std::endl; \
  ++acc; \
}

int main()
{
  std::cout << "Testing nmap_dns" << std::endl;

  int ret = 0;
  std::string target = "scanme.nmap.org";
  DNS::RECORD_TYPE rt = DNS::A;
  const size_t buflen = 1500;
  u8 buf[buflen];
  size_t reqlen = DNS::Factory::buildSimpleRequest(target, rt, buf, buflen);
  
  DNS::Packet p;
  size_t plen = p.parseFromBuffer(buf, buflen);
  TEST_INCR(reqlen == plen, ret);

  DNS::Query * q = &*p.queries.begin();
  TEST_INCR(q->name == target, ret);
  TEST_INCR(q->record_class == DNS::IN, ret);
  TEST_INCR(q->record_type == rt, ret);


  // This is a possible answere for an A query for scanme.nmap.org
  const char ipp[] = "45.33.32.156";
  const size_t answere_len = 49;
  const u8 answere_buf[] = { 0x92, 0xdc, // Trsnsaction ID
                       0x81, 0x80, // Flags
                       0x00, 0x01, // Questions count
                       0x00, 0x01, // Answers RRs count
                       0x00, 0x00, // Authorities RRs count
                       0x00, 0x00, // Additionals RRs count
                       0x06, // Label lenght <-- [12]
                       0x73, 0x63, 0x61, 0x6e, 0x6d, 0x65, // "scanme"
                       0x04, // Label lenght
                       0x6e, 0x6d, 0x61, 0x70, // "nmap"
                       0x03, // Label lenght
                       0x6f, 0x72, 0x67, // "org"
                       0x00, // Name terminator
                       0x00, 0x01, // A
                       0x00, 0x01, // IN
                       0xc0, 0x0c, // Compressed name pointer to offset 12
                       0x00, 0x01, // A
                       0x00, 0x01, // IN
                       0x00, 0x00, 0x0e, 0x0f, // TTL 3599
                       0x00, 0x04, // Record Lenght
                       0x2d, 0x21, 0x20, 0x9c }; // 45.33.32.156

  plen = p.parseFromBuffer(answere_buf, answere_len);
  TEST_INCR(answere_len == plen, ret);

  q = &*p.queries.begin();
  TEST_INCR(q->name == target, ret);
  TEST_INCR(q->record_class == DNS::IN, ret);
  TEST_INCR(q->record_type == rt, ret );

  DNS::Answer * a = &*p.answers.begin();
  TEST_INCR(a->name == target, ret );
  TEST_INCR(a->record_class == DNS::IN, ret);
  TEST_INCR(a->record_type == DNS::A, ret);
  TEST_INCR(a->ttl == 3599, ret)

  DNS::A_Record * ar = static_cast<DNS::A_Record *>(a->record);
  char ar_ipp[INET6_ADDRSTRLEN];
  sockaddr_storage_iptop(&ar->value, ar_ipp);
  TEST_INCR(!strcmp(ipp, ar_ipp), ret);

  const size_t ptr_answere_len = 72;
  std::string ptr_target;
  TEST_INCR(DNS::Factory::ipToPtr(ar->value, ptr_target), ret);
  TEST_INCR(ptr_target == "156.32.33.45.in-addr.arpa", ret);
  const u8 ptr_answere[] = { 0x08, 0xf2, // ID
                               0x81, 0x80, // Flags
                               0x00, 0x01, // Questions count
                               0x00, 0x01, // Answers RRs count
                               0x00, 0x00, // Authorities RRs count
                               0x00, 0x00, // Additionals RRs count
                               0x03, // Label lenght
                               0x31, 0x35, 0x36, // "156"
                               0x02, // Label lenght
                               0x33, 0x32, // "32"
                               0x02, // Label lenght
                               0x33, 0x33, // "33"
                               0x02, // Label lenght
                               0x34, 0x35, // "45"
                               0x07, // Label lenght
                               0x69, 0x6e, 0x2d, 0x61, 0x64, 0x64, 0x72, // "in-addr"
                               0x04, // Label lenght
                               0x61, 0x72, 0x70, 0x61, // "arpa"
                               0x00, // Name terminator
                               0x00, 0x0c, // PTR
                               0x00, 0x01, // IN
                               0xc0, 0x0c, // Compressed name pointer to offset 12
                               0x00, 0x0c, // PTR
                               0x00, 0x01, // IN
                               0x00, 0x01, 0x51, 0x78, // TTL 86392
                               0x00, 0x11, // Record Lenght
                               0x06, // Label lenght
                               0x73, 0x63, 0x61, 0x6e, 0x6d, 0x65, // "scanme"
                               0x04, // Label lenght
                               0x6e, 0x6d, 0x61, 0x70, // "nmap"
                               0x03, // Label lenght
                               0x6f, 0x72, 0x67, // "org"
                               0x00 };  // Name terminator

  plen = p.parseFromBuffer(ptr_answere, ptr_answere_len);
  TEST_INCR(plen == ptr_answere_len, ret);
  TEST_INCR(p.id == 0x08f2, ret);
  TEST_INCR(p.flags == 0x8180, ret);
  TEST_INCR(p.queries.size() == 1, ret);
  TEST_INCR(p.answers.size() == 1, ret);

  q = &*p.queries.begin();
  TEST_INCR(q->name == ptr_target, ret);
  TEST_INCR(q->record_class == DNS::IN, ret);
  TEST_INCR(q->record_type == DNS::PTR, ret);

  a = &*p.answers.begin();
  TEST_INCR(a->name == ptr_target, ret);
  TEST_INCR(a->record_class == DNS::IN, ret);
  TEST_INCR(a->record_type == DNS::PTR, ret);
  TEST_INCR(a->length == 0x11, ret);
  TEST_INCR(a->ttl == 86392, ret);

  DNS::PTR_Record * r = static_cast<DNS::PTR_Record *>(a->record);
  TEST_INCR(r->value == target, ret);

  if(ret) std::cout << "Testing nmap_dns finished with errors" << std::endl;
  else std::cout << "Testing nmap_dns finished without errors" << std::endl;

  return ret; // 0 means ok
}
