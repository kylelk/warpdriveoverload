#include"logger.h"
#include<cstdlib>
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<ctime>
#include<sys/types.h>
#include<unistd.h>
#include<boost/lexical_cast.hpp>

#include "tr1_threading.h"

#ifndef _GetPid
#define _GetPid getpid
#endif

logger::logger( const std::string lfile, const int llvl ) {
	L_logfile = lfile;
	L_loglevel = llvl;
	logToFile( "Warp Drive Overload Logging utility has started.", 6 );
}

void logger::logToFile( const std::string text, const int msglvl ) {
	L_pid = _GetPid();
	unsigned long TID = getThreadID();
	std::string date = tStamp();
	std::stringstream mstream;
	mstream << date << " [" << L_pid << "] (" << TID << ") [";
	switch ( msglvl ) {
		case 0:
			mstream << "DEBUG] :";
			break;
		case 1:
			mstream << "INFO] :";
			break;
		case 2:
			mstream << "WARNING] :";
			break;
		case 3:
			mstream << "ERROR] :";
			break;
		case 4:
			mstream << "CRIT] :";
			break;
		case 5:
			mstream << "FATAL] :";
			break;
		case 6:
			mstream << "INFO] :";
			break;
		default:
			mstream << "FATAL] : No message level passed to logger. Shutting down." << std::endl;
			std::string errstr = mstream.str();
			writeToFile( errstr );
			// placeholder for error handler.
			exit(1);
			break;
	}
	mstream << " " << text << std::endl;
	std::string logmsg = mstream.str();
	if ( msglvl >= L_loglevel ) {
		writeToFile( logmsg );
	}
}

unsigned long logger::getThreadID() {
	std::string threadID = boost::lexical_cast<std::string>(std::this_thread::get_id() );
	unsigned long threadnum = 0;
	sscanf( threadID.c_str(), "%lx", &threadnum );
	return threadnum;
}

void logger::logException( const int errornumber, const std::string ctext ) {
	std::stringstream exstream;
	int elvl;
	switch( errornumber ) {
		case 1000:
			exstream << "Error 1000: Invalid data passed to function, but was handled. " << ctext; // ctext should say something like "In function ___, line ___'
			elvl = 2;
			break;
		case 1001:
			exstream << "Error 1001: Invalid data passed to function was unhandled. " << ctext;
			elvl = 5;
			break;
		case 5000:
			exstream << "Error 5000: Thread Exited prematurely. " << ctext;
			elvl = 5;
			break;
		default:
			exstream << "Unhandled Error: An unhandled error code has been passed. " << ctext;
			elvl = 5;
			break;
	}
	std::string otext = exstream.str();
	logToFile( otext, elvl );
	if ( elvl > 4 ) {
		exit(1);
	}
}

std::string logger::tStamp() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime( &now );
	strftime( buf, sizeof(buf), "%Y-%m-%d %X", &tstruct );
	std::stringstream stampstream(buf);
	std::string tstamp = stampstream.str();
	return tstamp;
}

void logger::writeToFile( const std::string filetext ) {
	std::ofstream log_file( L_logfile, std::ofstream::app );
	log_file << filetext;
}
