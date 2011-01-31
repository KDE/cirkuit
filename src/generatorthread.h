/*
    Copyright (C) 2010  Matteo Agostinelli <agostinelli@gmail.com>

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

#ifndef GRAPHICSGENERATOR_H
#define GRAPHICSGENERATOR_H

#include "format.h"

#include <QThread>
#include <QImage>

class RenderThread;
namespace Cirkuit
{
class Command;
class Generator;
class Document;
class Backend;
}

class GeneratorThread : public QThread
{
    Q_OBJECT
public:
    GeneratorThread(const Cirkuit::Format& in, const Cirkuit::Format& out, Cirkuit::Document* doc = 0, QObject* parent = 0);
    ~GeneratorThread();
        
    Cirkuit::Generator* generator();
    
protected:
    Cirkuit::Format m_input, m_output;
    
public slots:
    void setup(const Cirkuit::Format& in, const Cirkuit::Format& out, Cirkuit::Backend* backend = 0, Cirkuit::Document* doc = 0, bool saveToFile = false);
    void run();
    
signals:
    void previewReady(const QImage);
    void fileReady(const QString);
    
    void error(const QString& appname, const QString& msg);
    void output(const QString& appname, const QString& msg);
    void fail();
    void success();
    
private:
    Cirkuit::Document* m_doc;
    Cirkuit::Backend* m_backend;
    
    RenderThread* m_render;
    bool m_saveToFile;
};

#endif // GRAPHICSGENERATOR_H
