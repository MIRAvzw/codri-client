/*
 * Copyright (C) 2006, 2007 Apple Inc.
 * Copyright (C) 2007 Alp Toker <alp@atoker.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *	notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

////////////////////////////////////////////////////////////////////////////////
// Configuration
//

#include <stdio.h>
#include <glib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "browser.h"

static pthread_t stdin_tid;

#define BUFFER_LENGTH   40



////////////////////////////////////////////////////////////////////////////////
// Threads
//

void*
stdin_thr() {
	printf("* Loaded STDIN thread\n");
	
	char line[BUFFER_LENGTH];
	char *p;
	
	// Available commands
	char cmdBack[] = "back";
	char cmdQuit[] = "quit";
	
	for (;;) {
		printf("> ");
		fflush (stdout);
		
		// Read and process
		p = fgets (line, BUFFER_LENGTH, stdin);		
		if (p != NULL) {
			// Remove endline
			int length = strlen(line)-1;
			if (line[length] == '\n')
				line[length] = '\0';
			
			// Process command
			if (strcmp(line, cmdBack) == 0)
				browser_go_back();
			else if (strcmp(line, cmdQuit) == 0)
				browser_quit();
			else
				printf("! Unknown command '%s'\n", line);
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Main
//

int
main (int argc, char* argv[])
{
	// Initialise
	browser_init();
	
	// Run
	pthread_create(&stdin_tid, NULL, stdin_thr, NULL);	
	browser_run();
	
	// Exit
	browser_exit();
	return 0;
}

