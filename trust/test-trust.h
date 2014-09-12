/*
 * Copyright (c) 2012 Red Hat Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the
 *       following disclaimer.
 *     * Redistributions in binary form must reproduce the
 *       above copyright notice, this list of conditions and
 *       the following disclaimer in the documentation and/or
 *       other materials provided with the distribution.
 *     * The names of contributors to this software may not be
 *       used to endorse or promote products derived from this
 *       software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * Author: Stef Walter <stefw@gnome.org>
 */

#include "dict.h"
#include "pkcs11.h"
#include "test.h"

#include <sys/types.h>
#include <stdlib.h>

#ifndef TEST_DATA_H_
#define TEST_DATA_H_

#define   test_check_object(attrs, klass, label) \
	test_check_object_msg (__FILE__, __LINE__, __FUNCTION__, attrs, klass, label)

void      test_check_object_msg        (const char *file,
                                        int line,
                                        const char *function,
                                        CK_ATTRIBUTE *attrs,
                                        CK_OBJECT_CLASS klass,
                                        const char *label);

#define   test_check_cacert3_ca(attrs, label) \
	test_check_cacert3_ca_msg (__FILE__, __LINE__, __FUNCTION__, attrs, label)

void      test_check_cacert3_ca_msg    (const char *file,
                                        int line,
                                        const char *function,
                                        CK_ATTRIBUTE *attrs,
                                        const char *label);

#define   test_check_attrs(expected, attrs) \
	test_check_attrs_msg (__FILE__, __LINE__, __FUNCTION__, expected, attrs)

void      test_check_attrs_msg         (const char *file,
                                        int line,
                                        const char *function,
                                        CK_ATTRIBUTE *expected,
                                        CK_ATTRIBUTE *attrs);

#define   test_check_attr(expected, attr) \
	test_check_attr_msg (__FILE__, __LINE__, __FUNCTION__, CKA_INVALID, expected, attr)

void      test_check_attr_msg          (const char *file,
                                        int line,
                                        const char *function,
                                        CK_OBJECT_CLASS klass,
                                        CK_ATTRIBUTE *expected,
                                        CK_ATTRIBUTE *attr);

#define   test_check_id(expected, attrs) \
	test_check_id_msg (__FILE__, __LINE__, __FUNCTION__, expected, attrs)

void      test_check_id_msg           (const char *file,
                                       int line,
                                       const char *function,
                                       CK_ATTRIBUTE *expected,
                                       CK_ATTRIBUTE *attr);

static const unsigned char test_cacert3_ca_der[] = {
	0x30, 0x82, 0x07, 0x59, 0x30, 0x82, 0x05, 0x41, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x03, 0x0a,
	0x41, 0x8a, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05,
	0x00, 0x30, 0x79, 0x31, 0x10, 0x30, 0x0e, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x07, 0x52, 0x6f,
	0x6f, 0x74, 0x20, 0x43, 0x41, 0x31, 0x1e, 0x30, 0x1c, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x15,
	0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x63, 0x61, 0x63, 0x65, 0x72,
	0x74, 0x2e, 0x6f, 0x72, 0x67, 0x31, 0x22, 0x30, 0x20, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x19,
	0x43, 0x41, 0x20, 0x43, 0x65, 0x72, 0x74, 0x20, 0x53, 0x69, 0x67, 0x6e, 0x69, 0x6e, 0x67, 0x20,
	0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x31, 0x21, 0x30, 0x1f, 0x06, 0x09, 0x2a,
	0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x09, 0x01, 0x16, 0x12, 0x73, 0x75, 0x70, 0x70, 0x6f, 0x72,
	0x74, 0x40, 0x63, 0x61, 0x63, 0x65, 0x72, 0x74, 0x2e, 0x6f, 0x72, 0x67, 0x30, 0x1e, 0x17, 0x0d,
	0x31, 0x31, 0x30, 0x35, 0x32, 0x33, 0x31, 0x37, 0x34, 0x38, 0x30, 0x32, 0x5a, 0x17, 0x0d, 0x32,
	0x31, 0x30, 0x35, 0x32, 0x30, 0x31, 0x37, 0x34, 0x38, 0x30, 0x32, 0x5a, 0x30, 0x54, 0x31, 0x14,
	0x30, 0x12, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0b, 0x43, 0x41, 0x63, 0x65, 0x72, 0x74, 0x20,
	0x49, 0x6e, 0x63, 0x2e, 0x31, 0x1e, 0x30, 0x1c, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x15, 0x68,
	0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x43, 0x41, 0x63, 0x65, 0x72, 0x74,
	0x2e, 0x6f, 0x72, 0x67, 0x31, 0x1c, 0x30, 0x1a, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x13, 0x43,
	0x41, 0x63, 0x65, 0x72, 0x74, 0x20, 0x43, 0x6c, 0x61, 0x73, 0x73, 0x20, 0x33, 0x20, 0x52, 0x6f,
	0x6f, 0x74, 0x30, 0x82, 0x02, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d,
	0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x02, 0x0f, 0x00, 0x30, 0x82, 0x02, 0x0a, 0x02, 0x82,
	0x02, 0x01, 0x00, 0xab, 0x49, 0x35, 0x11, 0x48, 0x7c, 0xd2, 0x26, 0x7e, 0x53, 0x94, 0xcf, 0x43,
	0xa9, 0xdd, 0x28, 0xd7, 0x42, 0x2a, 0x8b, 0xf3, 0x87, 0x78, 0x19, 0x58, 0x7c, 0x0f, 0x9e, 0xda,
	0x89, 0x7d, 0xe1, 0xfb, 0xeb, 0x72, 0x90, 0x0d, 0x74, 0xa1, 0x96, 0x64, 0xab, 0x9f, 0xa0, 0x24,
	0x99, 0x73, 0xda, 0xe2, 0x55, 0x76, 0xc7, 0x17, 0x7b, 0xf5, 0x04, 0xac, 0x46, 0xb8, 0xc3, 0xbe,
	0x7f, 0x64, 0x8d, 0x10, 0x6c, 0x24, 0xf3, 0x61, 0x9c, 0xc0, 0xf2, 0x90, 0xfa, 0x51, 0xe6, 0xf5,
	0x69, 0x01, 0x63, 0xc3, 0x0f, 0x56, 0xe2, 0x4a, 0x42, 0xcf, 0xe2, 0x44, 0x8c, 0x25, 0x28, 0xa8,
	0xc5, 0x79, 0x09, 0x7d, 0x46, 0xb9, 0x8a, 0xf3, 0xe9, 0xf3, 0x34, 0x29, 0x08, 0x45, 0xe4, 0x1c,
	0x9f, 0xcb, 0x94, 0x04, 0x1c, 0x81, 0xa8, 0x14, 0xb3, 0x98, 0x65, 0xc4, 0x43, 0xec, 0x4e, 0x82,
	0x8d, 0x09, 0xd1, 0xbd, 0xaa, 0x5b, 0x8d, 0x92, 0xd0, 0xec, 0xde, 0x90, 0xc5, 0x7f, 0x0a, 0xc2,
	0xe3, 0xeb, 0xe6, 0x31, 0x5a, 0x5e, 0x74, 0x3e, 0x97, 0x33, 0x59, 0xe8, 0xc3, 0x03, 0x3d, 0x60,
	0x33, 0xbf, 0xf7, 0xd1, 0x6f, 0x47, 0xc4, 0xcd, 0xee, 0x62, 0x83, 0x52, 0x6e, 0x2e, 0x08, 0x9a,
	0xa4, 0xd9, 0x15, 0x18, 0x91, 0xa6, 0x85, 0x92, 0x47, 0xb0, 0xae, 0x48, 0xeb, 0x6d, 0xb7, 0x21,
	0xec, 0x85, 0x1a, 0x68, 0x72, 0x35, 0xab, 0xff, 0xf0, 0x10, 0x5d, 0xc0, 0xf4, 0x94, 0xa7, 0x6a,
	0xd5, 0x3b, 0x92, 0x7e, 0x4c, 0x90, 0x05, 0x7e, 0x93, 0xc1, 0x2c, 0x8b, 0xa4, 0x8e, 0x62, 0x74,
	0x15, 0x71, 0x6e, 0x0b, 0x71, 0x03, 0xea, 0xaf, 0x15, 0x38, 0x9a, 0xd4, 0xd2, 0x05, 0x72, 0x6f,
	0x8c, 0xf9, 0x2b, 0xeb, 0x5a, 0x72, 0x25, 0xf9, 0x39, 0x46, 0xe3, 0x72, 0x1b, 0x3e, 0x04, 0xc3,
	0x64, 0x27, 0x22, 0x10, 0x2a, 0x8a, 0x4f, 0x58, 0xa7, 0x03, 0xad, 0xbe, 0xb4, 0x2e, 0x13, 0xed,
	0x5d, 0xaa, 0x48, 0xd7, 0xd5, 0x7d, 0xd4, 0x2a, 0x7b, 0x5c, 0xfa, 0x46, 0x04, 0x50, 0xe4, 0xcc,
	0x0e, 0x42, 0x5b, 0x8c, 0xed, 0xdb, 0xf2, 0xcf, 0xfc, 0x96, 0x93, 0xe0, 0xdb, 0x11, 0x36, 0x54,
	0x62, 0x34, 0x38, 0x8f, 0x0c, 0x60, 0x9b, 0x3b, 0x97, 0x56, 0x38, 0xad, 0xf3, 0xd2, 0x5b, 0x8b,
	0xa0, 0x5b, 0xea, 0x4e, 0x96, 0xb8, 0x7c, 0xd7, 0xd5, 0xa0, 0x86, 0x70, 0x40, 0xd3, 0x91, 0x29,
	0xb7, 0xa2, 0x3c, 0xad, 0xf5, 0x8c, 0xbb, 0xcf, 0x1a, 0x92, 0x8a, 0xe4, 0x34, 0x7b, 0xc0, 0xd8,
	0x6c, 0x5f, 0xe9, 0x0a, 0xc2, 0xc3, 0xa7, 0x20, 0x9a, 0x5a, 0xdf, 0x2c, 0x5d, 0x52, 0x5c, 0xba,
	0x47, 0xd5, 0x9b, 0xef, 0x24, 0x28, 0x70, 0x38, 0x20, 0x2f, 0xd5, 0x7f, 0x29, 0xc0, 0xb2, 0x41,
	0x03, 0x68, 0x92, 0xcc, 0xe0, 0x9c, 0xcc, 0x97, 0x4b, 0x45, 0xef, 0x3a, 0x10, 0x0a, 0xab, 0x70,
	0x3a, 0x98, 0x95, 0x70, 0xad, 0x35, 0xb1, 0xea, 0x85, 0x2b, 0xa4, 0x1c, 0x80, 0x21, 0x31, 0xa9,
	0xae, 0x60, 0x7a, 0x80, 0x26, 0x48, 0x00, 0xb8, 0x01, 0xc0, 0x93, 0x63, 0x55, 0x22, 0x91, 0x3c,
	0x56, 0xe7, 0xaf, 0xdb, 0x3a, 0x25, 0xf3, 0x8f, 0x31, 0x54, 0xea, 0x26, 0x8b, 0x81, 0x59, 0xf9,
	0xa1, 0xd1, 0x53, 0x11, 0xc5, 0x7b, 0x9d, 0x03, 0xf6, 0x74, 0x11, 0xe0, 0x6d, 0xb1, 0x2c, 0x3f,
	0x2c, 0x86, 0x91, 0x99, 0x71, 0x9a, 0xa6, 0x77, 0x8b, 0x34, 0x60, 0xd1, 0x14, 0xb4, 0x2c, 0xac,
	0x9d, 0xaf, 0x8c, 0x10, 0xd3, 0x9f, 0xc4, 0x6a, 0xf8, 0x6f, 0x13, 0xfc, 0x73, 0x59, 0xf7, 0x66,
	0x42, 0x74, 0x1e, 0x8a, 0xe3, 0xf8, 0xdc, 0xd2, 0x6f, 0x98, 0x9c, 0xcb, 0x47, 0x98, 0x95, 0x40,
	0x05, 0xfb, 0xe9, 0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x82, 0x02, 0x0d, 0x30, 0x82, 0x02, 0x09,
	0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14, 0x75, 0xa8, 0x71, 0x60, 0x4c,
	0x88, 0x13, 0xf0, 0x78, 0xd9, 0x89, 0x77, 0xb5, 0x6d, 0xc5, 0x89, 0xdf, 0xbc, 0xb1, 0x7a, 0x30,
	0x81, 0xa3, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x81, 0x9b, 0x30, 0x81, 0x98, 0x80, 0x14, 0x16,
	0xb5, 0x32, 0x1b, 0xd4, 0xc7, 0xf3, 0xe0, 0xe6, 0x8e, 0xf3, 0xbd, 0xd2, 0xb0, 0x3a, 0xee, 0xb2,
	0x39, 0x18, 0xd1, 0xa1, 0x7d, 0xa4, 0x7b, 0x30, 0x79, 0x31, 0x10, 0x30, 0x0e, 0x06, 0x03, 0x55,
	0x04, 0x0a, 0x13, 0x07, 0x52, 0x6f, 0x6f, 0x74, 0x20, 0x43, 0x41, 0x31, 0x1e, 0x30, 0x1c, 0x06,
	0x03, 0x55, 0x04, 0x0b, 0x13, 0x15, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77,
	0x2e, 0x63, 0x61, 0x63, 0x65, 0x72, 0x74, 0x2e, 0x6f, 0x72, 0x67, 0x31, 0x22, 0x30, 0x20, 0x06,
	0x03, 0x55, 0x04, 0x03, 0x13, 0x19, 0x43, 0x41, 0x20, 0x43, 0x65, 0x72, 0x74, 0x20, 0x53, 0x69,
	0x67, 0x6e, 0x69, 0x6e, 0x67, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x31,
	0x21, 0x30, 0x1f, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x09, 0x01, 0x16, 0x12,
	0x73, 0x75, 0x70, 0x70, 0x6f, 0x72, 0x74, 0x40, 0x63, 0x61, 0x63, 0x65, 0x72, 0x74, 0x2e, 0x6f,
	0x72, 0x67, 0x82, 0x01, 0x00, 0x30, 0x0f, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04,
	0x05, 0x30, 0x03, 0x01, 0x01, 0xff, 0x30, 0x5d, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07,
	0x01, 0x01, 0x04, 0x51, 0x30, 0x4f, 0x30, 0x23, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07,
	0x30, 0x01, 0x86, 0x17, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6f, 0x63, 0x73, 0x70, 0x2e,
	0x43, 0x41, 0x63, 0x65, 0x72, 0x74, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x30, 0x28, 0x06, 0x08, 0x2b,
	0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x02, 0x86, 0x1c, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f,
	0x77, 0x77, 0x77, 0x2e, 0x43, 0x41, 0x63, 0x65, 0x72, 0x74, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x63,
	0x61, 0x2e, 0x63, 0x72, 0x74, 0x30, 0x4a, 0x06, 0x03, 0x55, 0x1d, 0x20, 0x04, 0x43, 0x30, 0x41,
	0x30, 0x3f, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x04, 0x01, 0x81, 0x90, 0x4a, 0x30, 0x33, 0x30, 0x31,
	0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x02, 0x01, 0x16, 0x25, 0x68, 0x74, 0x74, 0x70,
	0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x43, 0x41, 0x63, 0x65, 0x72, 0x74, 0x2e, 0x6f, 0x72,
	0x67, 0x2f, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x2e, 0x70, 0x68, 0x70, 0x3f, 0x69, 0x64, 0x3d, 0x31,
	0x30, 0x30, 0x34, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x86, 0xf8, 0x42, 0x01, 0x08, 0x04, 0x27,
	0x16, 0x25, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x43, 0x41, 0x63,
	0x65, 0x72, 0x74, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x2e, 0x70, 0x68,
	0x70, 0x3f, 0x69, 0x64, 0x3d, 0x31, 0x30, 0x30, 0x50, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x86,
	0xf8, 0x42, 0x01, 0x0d, 0x04, 0x43, 0x16, 0x41, 0x54, 0x6f, 0x20, 0x67, 0x65, 0x74, 0x20, 0x79,
	0x6f, 0x75, 0x72, 0x20, 0x6f, 0x77, 0x6e, 0x20, 0x63, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63,
	0x61, 0x74, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x46, 0x52, 0x45, 0x45, 0x2c, 0x20, 0x67, 0x6f,
	0x20, 0x74, 0x6f, 0x20, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x43,
	0x41, 0x63, 0x65, 0x72, 0x74, 0x2e, 0x6f, 0x72, 0x67, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48,
	0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x03, 0x82, 0x02, 0x01, 0x00, 0x29, 0x28, 0x85,
	0xae, 0x44, 0xa9, 0xb9, 0xaf, 0xa4, 0x79, 0x13, 0xf0, 0xa8, 0xa3, 0x2b, 0x97, 0x60, 0xf3, 0x5c,
	0xee, 0xe3, 0x2f, 0xc1, 0xf6, 0xe2, 0x66, 0xa0, 0x11, 0xae, 0x36, 0x37, 0x3a, 0x76, 0x15, 0x04,
	0x53, 0xea, 0x42, 0xf5, 0xf9, 0xea, 0xc0, 0x15, 0xd8, 0xa6, 0x82, 0xd9, 0xe4, 0x61, 0xae, 0x72,
	0x0b, 0x29, 0x5c, 0x90, 0x43, 0xe8, 0x41, 0xb2, 0xe1, 0x77, 0xdb, 0x02, 0x13, 0x44, 0x78, 0x47,
	0x55, 0xaf, 0x58, 0xfc, 0xcc, 0x98, 0xf6, 0x45, 0xb9, 0xd1, 0x20, 0xf8, 0xd8, 0x21, 0x07, 0xfe,
	0x6d, 0xaa, 0x73, 0xd4, 0xb3, 0xc6, 0x07, 0xe9, 0x09, 0x85, 0xcc, 0x3b, 0xf2, 0xb6, 0xbe, 0x2c,
	0x1c, 0x25, 0xd5, 0x71, 0x8c, 0x39, 0xb5, 0x2e, 0xea, 0xbe, 0x18, 0x81, 0xba, 0xb0, 0x93, 0xb8,
	0x0f, 0xe3, 0xe6, 0xd7, 0x26, 0x8c, 0x31, 0x5a, 0x72, 0x03, 0x84, 0x52, 0xe6, 0xa6, 0xf5, 0x33,
	0x22, 0x45, 0x0a, 0xc8, 0x0b, 0x0d, 0x8a, 0xb8, 0x36, 0x6f, 0x90, 0x09, 0xa1, 0xab, 0xbd, 0xd7,
	0xd5, 0x4e, 0x2e, 0x71, 0xa2, 0xd4, 0xae, 0xfa, 0xa7, 0x54, 0x2b, 0xeb, 0x35, 0x8d, 0x5a, 0xb7,
	0x54, 0x88, 0x2f, 0xee, 0x74, 0x9f, 0xed, 0x48, 0x16, 0xca, 0x0d, 0x48, 0xd0, 0x94, 0xd3, 0xac,
	0xa4, 0xa2, 0xf6, 0x24, 0xdf, 0x92, 0xe3, 0xbd, 0xeb, 0x43, 0x40, 0x91, 0x6e, 0x1c, 0x18, 0x8e,
	0x56, 0xb4, 0x82, 0x12, 0xf3, 0xa9, 0x93, 0x9f, 0xd4, 0xbc, 0x9c, 0xad, 0x9c, 0x75, 0xee, 0x5a,
	0x97, 0x1b, 0x95, 0xe7, 0x74, 0x2d, 0x1c, 0x0f, 0xb0, 0x2c, 0x97, 0x9f, 0xfb, 0xa9, 0x33, 0x39,
	0x7a, 0xe7, 0x03, 0x3a, 0x92, 0x8e, 0x22, 0xf6, 0x8c, 0x0d, 0xe4, 0xd9, 0x7e, 0x0d, 0x76, 0x18,
	0xf7, 0x01, 0xf9, 0xef, 0x96, 0x96, 0xa2, 0x55, 0x73, 0xc0, 0x3c, 0x71, 0xb4, 0x1d, 0x1a, 0x56,
	0x43, 0xb7, 0xc3, 0x0a, 0x8d, 0x72, 0xfc, 0xe2, 0x10, 0x09, 0x0b, 0x41, 0xce, 0x8c, 0x94, 0xa0,
	0xf9, 0x03, 0xfd, 0x71, 0x73, 0x4b, 0x8a, 0x57, 0x33, 0xe5, 0x8e, 0x74, 0x7e, 0x15, 0x01, 0x00,
	0xe6, 0xcc, 0x4a, 0x1c, 0xe7, 0x7f, 0x95, 0x19, 0x2d, 0xc5, 0xa5, 0x0c, 0x8b, 0xbb, 0xb5, 0xed,
	0x85, 0xb3, 0x5c, 0xd3, 0xdf, 0xb8, 0xb9, 0xf2, 0xca, 0xc7, 0x0d, 0x01, 0x14, 0xac, 0x70, 0x58,
	0xc5, 0x8c, 0x8d, 0x33, 0xd4, 0x9d, 0x66, 0xa3, 0x1a, 0x50, 0x95, 0x23, 0xfc, 0x48, 0xe0, 0x06,
	0x43, 0x12, 0xd9, 0xcd, 0xa7, 0x86, 0x39, 0x2f, 0x36, 0x72, 0xa3, 0x80, 0x10, 0xe4, 0xe1, 0xf3,
	0xd1, 0xcb, 0x5b, 0x1a, 0xc0, 0xe4, 0x80, 0x9a, 0x7c, 0x13, 0x73, 0x06, 0x4f, 0xdb, 0xa3, 0x6b,
	0x24, 0x0a, 0xba, 0xb3, 0x1c, 0xbc, 0x4a, 0x78, 0xbb, 0xe5, 0xe3, 0x75, 0x38, 0xa5, 0x48, 0xa7,
	0xa2, 0x1e, 0xaf, 0x76, 0xd4, 0x5e, 0xf7, 0x38, 0x86, 0x56, 0x5a, 0x89, 0xce, 0xd6, 0xc3, 0xa7,
	0x79, 0xb2, 0x52, 0xa0, 0xc6, 0xf1, 0x85, 0xb4, 0x25, 0x8c, 0xf2, 0x3f, 0x96, 0xb3, 0x10, 0xd9,
	0x8d, 0x6c, 0x57, 0x3b, 0x9f, 0x6f, 0x86, 0x3a, 0x18, 0x82, 0x22, 0x36, 0xc8, 0xb0, 0x91, 0x38,
	0xdb, 0x2a, 0xa1, 0x93, 0xaa, 0x84, 0x3f, 0xf5, 0x27, 0x65, 0xae, 0x73, 0xd5, 0xc8, 0xd5, 0xd3,
	0x77, 0xea, 0x4b, 0x9d, 0xc7, 0x41, 0xbb, 0xc7, 0xc0, 0xe3, 0xa0, 0x3f, 0xe4, 0x7d, 0xa4, 0x8d,
	0x73, 0xe6, 0x12, 0x4b, 0xdf, 0xa1, 0x73, 0x73, 0x73, 0x3a, 0x80, 0xe8, 0xd5, 0xcb, 0x8e, 0x2f,
	0xcb, 0xea, 0x13, 0xa7, 0xd6, 0x41, 0x8b, 0xac, 0xfa, 0x3c, 0x89, 0xd7, 0x24, 0xf5, 0x4e, 0xb4,
	0xe0, 0x61, 0x92, 0xb7, 0xf3, 0x37, 0x98, 0xc4, 0xbe, 0x96, 0xa3, 0xb7, 0x8a,
};

static const char test_cacert3_ca_subject[] = {
	0x30, 0x54, 0x31, 0x14, 0x30, 0x12, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0b, 0x43, 0x41, 0x63,
	0x65, 0x72, 0x74, 0x20, 0x49, 0x6e, 0x63, 0x2e, 0x31, 0x1e, 0x30, 0x1c, 0x06, 0x03, 0x55, 0x04,
	0x0b, 0x13, 0x15, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x43, 0x41,
	0x63, 0x65, 0x72, 0x74, 0x2e, 0x6f, 0x72, 0x67, 0x31, 0x1c, 0x30, 0x1a, 0x06, 0x03, 0x55, 0x04,
	0x03, 0x13, 0x13, 0x43, 0x41, 0x63, 0x65, 0x72, 0x74, 0x20, 0x43, 0x6c, 0x61, 0x73, 0x73, 0x20,
	0x33, 0x20, 0x52, 0x6f, 0x6f, 0x74,
};

static const char test_cacert3_ca_issuer[] = {
	0x30, 0x79, 0x31, 0x10, 0x30, 0x0e, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x07, 0x52, 0x6f, 0x6f,
	0x74, 0x20, 0x43, 0x41, 0x31, 0x1e, 0x30, 0x1c, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x15, 0x68,
	0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x63, 0x61, 0x63, 0x65, 0x72, 0x74,
	0x2e, 0x6f, 0x72, 0x67, 0x31, 0x22, 0x30, 0x20, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x19, 0x43,
	0x41, 0x20, 0x43, 0x65, 0x72, 0x74, 0x20, 0x53, 0x69, 0x67, 0x6e, 0x69, 0x6e, 0x67, 0x20, 0x41,
	0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x31, 0x21, 0x30, 0x1f, 0x06, 0x09, 0x2a, 0x86,
	0x48, 0x86, 0xf7, 0x0d, 0x01, 0x09, 0x01, 0x16, 0x12, 0x73, 0x75, 0x70, 0x70, 0x6f, 0x72, 0x74,
	0x40, 0x63, 0x61, 0x63, 0x65, 0x72, 0x74, 0x2e, 0x6f, 0x72, 0x67,
};

static const char test_cacert3_ca_serial[] = {
	0x02, 0x03, 0x0a, 0x41, 0x8a,
};

static const char test_cacert3_ca_public_key[] = {
	0x30, 0x82, 0x02, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
	0x01, 0x05, 0x00, 0x03, 0x82, 0x02, 0x0f, 0x00, 0x30, 0x82, 0x02, 0x0a, 0x02, 0x82, 0x02, 0x01,
	0x00, 0xab, 0x49, 0x35, 0x11, 0x48, 0x7c, 0xd2, 0x26, 0x7e, 0x53, 0x94, 0xcf, 0x43, 0xa9, 0xdd,
	0x28, 0xd7, 0x42, 0x2a, 0x8b, 0xf3, 0x87, 0x78, 0x19, 0x58, 0x7c, 0x0f, 0x9e, 0xda, 0x89, 0x7d,
	0xe1, 0xfb, 0xeb, 0x72, 0x90, 0x0d, 0x74, 0xa1, 0x96, 0x64, 0xab, 0x9f, 0xa0, 0x24, 0x99, 0x73,
	0xda, 0xe2, 0x55, 0x76, 0xc7, 0x17, 0x7b, 0xf5, 0x04, 0xac, 0x46, 0xb8, 0xc3, 0xbe, 0x7f, 0x64,
	0x8d, 0x10, 0x6c, 0x24, 0xf3, 0x61, 0x9c, 0xc0, 0xf2, 0x90, 0xfa, 0x51, 0xe6, 0xf5, 0x69, 0x01,
	0x63, 0xc3, 0x0f, 0x56, 0xe2, 0x4a, 0x42, 0xcf, 0xe2, 0x44, 0x8c, 0x25, 0x28, 0xa8, 0xc5, 0x79,
	0x09, 0x7d, 0x46, 0xb9, 0x8a, 0xf3, 0xe9, 0xf3, 0x34, 0x29, 0x08, 0x45, 0xe4, 0x1c, 0x9f, 0xcb,
	0x94, 0x04, 0x1c, 0x81, 0xa8, 0x14, 0xb3, 0x98, 0x65, 0xc4, 0x43, 0xec, 0x4e, 0x82, 0x8d, 0x09,
	0xd1, 0xbd, 0xaa, 0x5b, 0x8d, 0x92, 0xd0, 0xec, 0xde, 0x90, 0xc5, 0x7f, 0x0a, 0xc2, 0xe3, 0xeb,
	0xe6, 0x31, 0x5a, 0x5e, 0x74, 0x3e, 0x97, 0x33, 0x59, 0xe8, 0xc3, 0x03, 0x3d, 0x60, 0x33, 0xbf,
	0xf7, 0xd1, 0x6f, 0x47, 0xc4, 0xcd, 0xee, 0x62, 0x83, 0x52, 0x6e, 0x2e, 0x08, 0x9a, 0xa4, 0xd9,
	0x15, 0x18, 0x91, 0xa6, 0x85, 0x92, 0x47, 0xb0, 0xae, 0x48, 0xeb, 0x6d, 0xb7, 0x21, 0xec, 0x85,
	0x1a, 0x68, 0x72, 0x35, 0xab, 0xff, 0xf0, 0x10, 0x5d, 0xc0, 0xf4, 0x94, 0xa7, 0x6a, 0xd5, 0x3b,
	0x92, 0x7e, 0x4c, 0x90, 0x05, 0x7e, 0x93, 0xc1, 0x2c, 0x8b, 0xa4, 0x8e, 0x62, 0x74, 0x15, 0x71,
	0x6e, 0x0b, 0x71, 0x03, 0xea, 0xaf, 0x15, 0x38, 0x9a, 0xd4, 0xd2, 0x05, 0x72, 0x6f, 0x8c, 0xf9,
	0x2b, 0xeb, 0x5a, 0x72, 0x25, 0xf9, 0x39, 0x46, 0xe3, 0x72, 0x1b, 0x3e, 0x04, 0xc3, 0x64, 0x27,
	0x22, 0x10, 0x2a, 0x8a, 0x4f, 0x58, 0xa7, 0x03, 0xad, 0xbe, 0xb4, 0x2e, 0x13, 0xed, 0x5d, 0xaa,
	0x48, 0xd7, 0xd5, 0x7d, 0xd4, 0x2a, 0x7b, 0x5c, 0xfa, 0x46, 0x04, 0x50, 0xe4, 0xcc, 0x0e, 0x42,
	0x5b, 0x8c, 0xed, 0xdb, 0xf2, 0xcf, 0xfc, 0x96, 0x93, 0xe0, 0xdb, 0x11, 0x36, 0x54, 0x62, 0x34,
	0x38, 0x8f, 0x0c, 0x60, 0x9b, 0x3b, 0x97, 0x56, 0x38, 0xad, 0xf3, 0xd2, 0x5b, 0x8b, 0xa0, 0x5b,
	0xea, 0x4e, 0x96, 0xb8, 0x7c, 0xd7, 0xd5, 0xa0, 0x86, 0x70, 0x40, 0xd3, 0x91, 0x29, 0xb7, 0xa2,
	0x3c, 0xad, 0xf5, 0x8c, 0xbb, 0xcf, 0x1a, 0x92, 0x8a, 0xe4, 0x34, 0x7b, 0xc0, 0xd8, 0x6c, 0x5f,
	0xe9, 0x0a, 0xc2, 0xc3, 0xa7, 0x20, 0x9a, 0x5a, 0xdf, 0x2c, 0x5d, 0x52, 0x5c, 0xba, 0x47, 0xd5,
	0x9b, 0xef, 0x24, 0x28, 0x70, 0x38, 0x20, 0x2f, 0xd5, 0x7f, 0x29, 0xc0, 0xb2, 0x41, 0x03, 0x68,
	0x92, 0xcc, 0xe0, 0x9c, 0xcc, 0x97, 0x4b, 0x45, 0xef, 0x3a, 0x10, 0x0a, 0xab, 0x70, 0x3a, 0x98,
	0x95, 0x70, 0xad, 0x35, 0xb1, 0xea, 0x85, 0x2b, 0xa4, 0x1c, 0x80, 0x21, 0x31, 0xa9, 0xae, 0x60,
	0x7a, 0x80, 0x26, 0x48, 0x00, 0xb8, 0x01, 0xc0, 0x93, 0x63, 0x55, 0x22, 0x91, 0x3c, 0x56, 0xe7,
	0xaf, 0xdb, 0x3a, 0x25, 0xf3, 0x8f, 0x31, 0x54, 0xea, 0x26, 0x8b, 0x81, 0x59, 0xf9, 0xa1, 0xd1,
	0x53, 0x11, 0xc5, 0x7b, 0x9d, 0x03, 0xf6, 0x74, 0x11, 0xe0, 0x6d, 0xb1, 0x2c, 0x3f, 0x2c, 0x86,
	0x91, 0x99, 0x71, 0x9a, 0xa6, 0x77, 0x8b, 0x34, 0x60, 0xd1, 0x14, 0xb4, 0x2c, 0xac, 0x9d, 0xaf,
	0x8c, 0x10, 0xd3, 0x9f, 0xc4, 0x6a, 0xf8, 0x6f, 0x13, 0xfc, 0x73, 0x59, 0xf7, 0x66, 0x42, 0x74,
	0x1e, 0x8a, 0xe3, 0xf8, 0xdc, 0xd2, 0x6f, 0x98, 0x9c, 0xcb, 0x47, 0x98, 0x95, 0x40, 0x05, 0xfb,
	0xe9, 0x02, 0x03, 0x01, 0x00, 0x01,
};

static const unsigned char verisign_v1_ca[] = {
	0x30, 0x82, 0x02, 0x3c, 0x30, 0x82, 0x01, 0xa5, 0x02, 0x10, 0x3f, 0x69, 0x1e, 0x81, 0x9c, 0xf0,
	0x9a, 0x4a, 0xf3, 0x73, 0xff, 0xb9, 0x48, 0xa2, 0xe4, 0xdd, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86,
	0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x30, 0x5f, 0x31, 0x0b, 0x30, 0x09, 0x06,
	0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x17, 0x30, 0x15, 0x06, 0x03, 0x55, 0x04,
	0x0a, 0x13, 0x0e, 0x56, 0x65, 0x72, 0x69, 0x53, 0x69, 0x67, 0x6e, 0x2c, 0x20, 0x49, 0x6e, 0x63,
	0x2e, 0x31, 0x37, 0x30, 0x35, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x2e, 0x43, 0x6c, 0x61, 0x73,
	0x73, 0x20, 0x31, 0x20, 0x50, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x50, 0x72, 0x69, 0x6d, 0x61,
	0x72, 0x79, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e,
	0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x30, 0x1e, 0x17, 0x0d, 0x39, 0x36,
	0x30, 0x31, 0x32, 0x39, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x5a, 0x17, 0x0d, 0x32, 0x38, 0x30,
	0x38, 0x30, 0x32, 0x32, 0x33, 0x35, 0x39, 0x35, 0x39, 0x5a, 0x30, 0x5f, 0x31, 0x0b, 0x30, 0x09,
	0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x17, 0x30, 0x15, 0x06, 0x03, 0x55,
	0x04, 0x0a, 0x13, 0x0e, 0x56, 0x65, 0x72, 0x69, 0x53, 0x69, 0x67, 0x6e, 0x2c, 0x20, 0x49, 0x6e,
	0x63, 0x2e, 0x31, 0x37, 0x30, 0x35, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x2e, 0x43, 0x6c, 0x61,
	0x73, 0x73, 0x20, 0x31, 0x20, 0x50, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x20, 0x50, 0x72, 0x69, 0x6d,
	0x61, 0x72, 0x79, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f,
	0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x30, 0x81, 0x9f, 0x30, 0x0d,
	0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x81, 0x8d,
	0x00, 0x30, 0x81, 0x89, 0x02, 0x81, 0x81, 0x00, 0xe5, 0x19, 0xbf, 0x6d, 0xa3, 0x56, 0x61, 0x2d,
	0x99, 0x48, 0x71, 0xf6, 0x67, 0xde, 0xb9, 0x8d, 0xeb, 0xb7, 0x9e, 0x86, 0x80, 0x0a, 0x91, 0x0e,
	0xfa, 0x38, 0x25, 0xaf, 0x46, 0x88, 0x82, 0xe5, 0x73, 0xa8, 0xa0, 0x9b, 0x24, 0x5d, 0x0d, 0x1f,
	0xcc, 0x65, 0x6e, 0x0c, 0xb0, 0xd0, 0x56, 0x84, 0x18, 0x87, 0x9a, 0x06, 0x9b, 0x10, 0xa1, 0x73,
	0xdf, 0xb4, 0x58, 0x39, 0x6b, 0x6e, 0xc1, 0xf6, 0x15, 0xd5, 0xa8, 0xa8, 0x3f, 0xaa, 0x12, 0x06,
	0x8d, 0x31, 0xac, 0x7f, 0xb0, 0x34, 0xd7, 0x8f, 0x34, 0x67, 0x88, 0x09, 0xcd, 0x14, 0x11, 0xe2,
	0x4e, 0x45, 0x56, 0x69, 0x1f, 0x78, 0x02, 0x80, 0xda, 0xdc, 0x47, 0x91, 0x29, 0xbb, 0x36, 0xc9,
	0x63, 0x5c, 0xc5, 0xe0, 0xd7, 0x2d, 0x87, 0x7b, 0xa1, 0xb7, 0x32, 0xb0, 0x7b, 0x30, 0xba, 0x2a,
	0x2f, 0x31, 0xaa, 0xee, 0xa3, 0x67, 0xda, 0xdb, 0x02, 0x03, 0x01, 0x00, 0x01, 0x30, 0x0d, 0x06,
	0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x81, 0x81, 0x00,
	0x58, 0x15, 0x29, 0x39, 0x3c, 0x77, 0xa3, 0xda, 0x5c, 0x25, 0x03, 0x7c, 0x60, 0xfa, 0xee, 0x09,
	0x99, 0x3c, 0x27, 0x10, 0x70, 0xc8, 0x0c, 0x09, 0xe6, 0xb3, 0x87, 0xcf, 0x0a, 0xe2, 0x18, 0x96,
	0x35, 0x62, 0xcc, 0xbf, 0x9b, 0x27, 0x79, 0x89, 0x5f, 0xc9, 0xc4, 0x09, 0xf4, 0xce, 0xb5, 0x1d,
	0xdf, 0x2a, 0xbd, 0xe5, 0xdb, 0x86, 0x9c, 0x68, 0x25, 0xe5, 0x30, 0x7c, 0xb6, 0x89, 0x15, 0xfe,
	0x67, 0xd1, 0xad, 0xe1, 0x50, 0xac, 0x3c, 0x7c, 0x62, 0x4b, 0x8f, 0xba, 0x84, 0xd7, 0x12, 0x15,
	0x1b, 0x1f, 0xca, 0x5d, 0x0f, 0xc1, 0x52, 0x94, 0x2a, 0x11, 0x99, 0xda, 0x7b, 0xcf, 0x0c, 0x36,
	0x13, 0xd5, 0x35, 0xdc, 0x10, 0x19, 0x59, 0xea, 0x94, 0xc1, 0x00, 0xbf, 0x75, 0x8f, 0xd9, 0xfa,
	0xfd, 0x76, 0x04, 0xdb, 0x62, 0xbb, 0x90, 0x6a, 0x03, 0xd9, 0x46, 0x35, 0xd9, 0xf8, 0x7c, 0x5b,
};

static const unsigned char verisign_v1_ca_subject[] = {
	0x30, 0x5f, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31,
	0x17, 0x30, 0x15, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0e, 0x56, 0x65, 0x72, 0x69, 0x53, 0x69,
	0x67, 0x6e, 0x2c, 0x20, 0x49, 0x6e, 0x63, 0x2e, 0x31, 0x37, 0x30, 0x35, 0x06, 0x03, 0x55, 0x04,
	0x0b, 0x13, 0x2e, 0x43, 0x6c, 0x61, 0x73, 0x73, 0x20, 0x31, 0x20, 0x50, 0x75, 0x62, 0x6c, 0x69,
	0x63, 0x20, 0x50, 0x72, 0x69, 0x6d, 0x61, 0x72, 0x79, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66,
	0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74,
	0x79,
};

static const unsigned char verisign_v1_ca_public_key[] = {
	0x30, 0x81, 0x9f, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01,
	0x05, 0x00, 0x03, 0x81, 0x8d, 0x00, 0x30, 0x81, 0x89, 0x02, 0x81, 0x81, 0x00, 0xe5, 0x19, 0xbf,
	0x6d, 0xa3, 0x56, 0x61, 0x2d, 0x99, 0x48, 0x71, 0xf6, 0x67, 0xde, 0xb9, 0x8d, 0xeb, 0xb7, 0x9e,
	0x86, 0x80, 0x0a, 0x91, 0x0e, 0xfa, 0x38, 0x25, 0xaf, 0x46, 0x88, 0x82, 0xe5, 0x73, 0xa8, 0xa0,
	0x9b, 0x24, 0x5d, 0x0d, 0x1f, 0xcc, 0x65, 0x6e, 0x0c, 0xb0, 0xd0, 0x56, 0x84, 0x18, 0x87, 0x9a,
	0x06, 0x9b, 0x10, 0xa1, 0x73, 0xdf, 0xb4, 0x58, 0x39, 0x6b, 0x6e, 0xc1, 0xf6, 0x15, 0xd5, 0xa8,
	0xa8, 0x3f, 0xaa, 0x12, 0x06, 0x8d, 0x31, 0xac, 0x7f, 0xb0, 0x34, 0xd7, 0x8f, 0x34, 0x67, 0x88,
	0x09, 0xcd, 0x14, 0x11, 0xe2, 0x4e, 0x45, 0x56, 0x69, 0x1f, 0x78, 0x02, 0x80, 0xda, 0xdc, 0x47,
	0x91, 0x29, 0xbb, 0x36, 0xc9, 0x63, 0x5c, 0xc5, 0xe0, 0xd7, 0x2d, 0x87, 0x7b, 0xa1, 0xb7, 0x32,
	0xb0, 0x7b, 0x30, 0xba, 0x2a, 0x2f, 0x31, 0xaa, 0xee, 0xa3, 0x67, 0xda, 0xdb, 0x02, 0x03, 0x01,
	0x00, 0x01,
};

static const unsigned char example_public_key[] = {
	0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
	0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01,
	0x00, 0xaf, 0x24, 0x08, 0x08, 0x29, 0x7a, 0x35, 0x9e, 0x60, 0x0c, 0xaa, 0xe7, 0x4b, 0x3b, 0x4e,
	0xdc, 0x7c, 0xbc, 0x3c, 0x45, 0x1c, 0xbb, 0x2b, 0xe0, 0xfe, 0x29, 0x02, 0xf9, 0x57, 0x08, 0xa3,
	0x64, 0x85, 0x15, 0x27, 0xf5, 0xf1, 0xad, 0xc8, 0x31, 0x89, 0x5d, 0x22, 0xe8, 0x2a, 0xaa, 0xa6,
	0x42, 0xb3, 0x8f, 0xf8, 0xb9, 0x55, 0xb7, 0xb1, 0xb7, 0x4b, 0xb3, 0xfe, 0x8f, 0x7e, 0x07, 0x57,
	0xec, 0xef, 0x43, 0xdb, 0x66, 0x62, 0x15, 0x61, 0xcf, 0x60, 0x0d, 0xa4, 0xd8, 0xde, 0xf8, 0xe0,
	0xc3, 0x62, 0x08, 0x3d, 0x54, 0x13, 0xeb, 0x49, 0xca, 0x59, 0x54, 0x85, 0x26, 0xe5, 0x2b, 0x8f,
	0x1b, 0x9f, 0xeb, 0xf5, 0xa1, 0x91, 0xc2, 0x33, 0x49, 0xd8, 0x43, 0x63, 0x6a, 0x52, 0x4b, 0xd2,
	0x8f, 0xe8, 0x70, 0x51, 0x4d, 0xd1, 0x89, 0x69, 0x7b, 0xc7, 0x70, 0xf6, 0xb3, 0xdc, 0x12, 0x74,
	0xdb, 0x7b, 0x5d, 0x4b, 0x56, 0xd3, 0x96, 0xbf, 0x15, 0x77, 0xa1, 0xb0, 0xf4, 0xa2, 0x25, 0xf2,
	0xaf, 0x1c, 0x92, 0x67, 0x18, 0xe5, 0xf4, 0x06, 0x04, 0xef, 0x90, 0xb9, 0xe4, 0x00, 0xe4, 0xdd,
	0x3a, 0xb5, 0x19, 0xff, 0x02, 0xba, 0xf4, 0x3c, 0xee, 0xe0, 0x8b, 0xeb, 0x37, 0x8b, 0xec, 0xf4,
	0xd7, 0xac, 0xf2, 0xf6, 0xf0, 0x3d, 0xaf, 0xdd, 0x75, 0x91, 0x33, 0x19, 0x1d, 0x1c, 0x40, 0xcb,
	0x74, 0x24, 0x19, 0x21, 0x93, 0xd9, 0x14, 0xfe, 0xac, 0x2a, 0x52, 0xc7, 0x8f, 0xd5, 0x04, 0x49,
	0xe4, 0x8d, 0x63, 0x47, 0x88, 0x3c, 0x69, 0x83, 0xcb, 0xfe, 0x47, 0xbd, 0x2b, 0x7e, 0x4f, 0xc5,
	0x95, 0xae, 0x0e, 0x9d, 0xd4, 0xd1, 0x43, 0xc0, 0x67, 0x73, 0xe3, 0x14, 0x08, 0x7e, 0xe5, 0x3f,
	0x9f, 0x73, 0xb8, 0x33, 0x0a, 0xcf, 0x5d, 0x3f, 0x34, 0x87, 0x96, 0x8a, 0xee, 0x53, 0xe8, 0x25,
	0x15, 0x02, 0x03, 0x01, 0x00, 0x01
};

static const char test_text[] = "This is the file text";

static const char test_eku_server_and_client[] = {
	0x30, 0x14, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x01, 0x06, 0x08, 0x2b, 0x06,
	0x01, 0x05, 0x05, 0x07, 0x03, 0x02,
};

static const char test_eku_server[] = {
	0x30, 0x0a, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x01,
};

static const char test_eku_email[] = {
	0x30, 0x0a, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x04
};

static const char test_eku_none[] = {
	0x30, 0x00,
};

void       test_check_file_msg          (const char *file,
                                         int line,
                                         const char *function,
                                         const char *directory,
                                         const char *filename,
                                         const char *reference);

void       test_check_data_msg          (const char *file,
                                         int line,
                                         const char *function,
                                         const char *directory,
                                         const char *filename,
                                         const void *refdata,
                                         long reflen);

#ifdef OS_UNIX

void       test_check_symlink_msg       (const char *file,
                                         int line,
                                         const char *function,
                                         const char *directory,
                                         const char *name,
                                         const char *destination);

#endif /* OS_UNIX */

p11_dict * test_check_directory_files   (const char *file,
                                         ...) GNUC_NULL_TERMINATED;

void       test_check_directory_msg     (const char *file,
                                         int line,
                                         const char *function,
                                         const char *directory,
                                         p11_dict *files);

#define test_check_file(directory, name, reference) \
	(test_check_file_msg (__FILE__, __LINE__, __FUNCTION__, directory, name, reference))

#define test_check_data(directory, name, data, length) \
	(test_check_data_msg (__FILE__, __LINE__, __FUNCTION__, directory, name, data, length))

#ifdef OS_UNIX

#define test_check_symlink(directory, name, destination) \
	(test_check_symlink_msg (__FILE__, __LINE__, __FUNCTION__, directory, name, destination))

#endif /* OS_UNIX */

#define test_check_directory(directory, files) \
	(test_check_directory_msg (__FILE__, __LINE__, __FUNCTION__, directory, \
	                           test_check_directory_files files))

#endif /* TEST_DATA_H_ */
