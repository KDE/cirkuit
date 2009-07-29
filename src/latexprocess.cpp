/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "latexprocess.h"
#include <KStandardDirs>

LatexProcess::LatexProcess(const QString& jobName, const QString& interpreter, QObject* parent): ExternalProcess(interpreter, parent), m_jobName(jobName), m_interpreter(interpreter)
{
	
}

bool LatexProcess::build(const QString& doc)
{
	QStringList args;
	
	QStringList environment = QProcess::systemEnvironment();
	// the following enviroment variable is needed to find boxdims.sty in the circuit maaros distribution
	environment << QString("TEXINPUTS=.:%1:").arg(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", false));
	setEnvironment(environment);
	
	args << QString("-jobname=%1").arg(m_jobName);
	
	start(m_appName, args);
	
	if (!waitForStarted())
		return false;
	
	write(doc.toLatin1());
	closeWriteChannel();
	
	if (!waitForFinished())
		return false;	
	
	return true;
}