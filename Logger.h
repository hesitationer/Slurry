#pragma once

#include <QSharedPointer>
#include <QString>

class QMutex;
class QFile;
class QTextStream;

class Logger
{

public:
	virtual ~Logger();

	static void PrintLog(const QString &msg);	//����text��������ʾ
	static void WriteLog(const QString &msg);	//��д����־�ļ�
	static void Debug(const QString &msg);	//�ڿ���̨���
	static void WarnAndQuit(const QString &msg); //�ؼ��ļ����� ���沢�˳�

	//qDebug() qWarning() qCritical() qFatal() 

	static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

protected:
	Logger();

private:
	Logger(const Logger&);
	void operator = (const Logger &);

	static Logger *GetInstance();
	static QMutex *mutex;
	static QFile *file;
	static QTextStream *text_stream;
	static QSharedPointer<Logger> pInst;
};

//д����־�ļ��� Cosole����̨
