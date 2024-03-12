#pragma once
//�ε������ ����
enum class LOAD_KIND
{
	LOAD_KIND_IMAGE,			//�Ϲ� �̹���
	LOAD_KIND_FRAMEIMAGE,		//������ �̹���
	LOAD_KIND_SOUND,			//����
	LOAD_KIND_SCENE,			//��
};

//���̹��� ���ҽ� ����ü
struct tagImageResource
{
	std::string keyName;		//�̹��� Ű��
	std::wstring fileName;		//�����̸�
	int frameX;					//������ �̹����� ������X ����
	int frameY;					//������ �̹����� ������Y ����
};

//����� ���ҽ� ����ü
struct tagSoundResource
{
	std::string keyName;		//�̹���Ű��
	std::string fileName;		//���� �̸�
	bool bgm;					//������� ����
	bool loop;					//�������� ����
};

//����� ������ ����ü
struct tagSceneResource
{
	std::string sceneName;
	Scene* scene;
};

//=============================================================
//	## loadItem ## (�ε������ Ŭ����)
//=============================================================

class LoadItem
{
private:
	LOAD_KIND _kind; //�ε� ����
	tagImageResource _imageResource;
	tagSoundResource _soundResource;
	tagSceneResource _sceneResource;
	wstring name;

public:
	//�Ϲ� �̹���
	HRESULT Init(std::string keyName, std::wstring fileName);
	//������ �̹��� ���� �ʱ�ȭ(�ֻ��)
	HRESULT Init(std::string keyName, std::wstring fileName,int frameX, int frameY);
	//���� �ε�
	HRESULT Init(std::string keyName, std::string fileName, bool bgm, bool loop);

	//�ε������� ���� ��������
	LOAD_KIND GetLoadingKind() { return _kind; }

	//�̹��� ���ҽ� ��������
	tagImageResource GetImageResource() { return _imageResource; }
	tagSoundResource GetSoundResource() { return _soundResource; }
	tagSceneResource GetSceneResource() { return _sceneResource; }
	wstring GetName() { return name; }

	LoadItem() {}
	~LoadItem() {}
};


//=============================================================
//	## loading ## (�ε� Ŭ����)
//=============================================================
class Loading 
{
private:
	//��ε��� �����۵� ���� ���� �� ���ͷ�����
	typedef std::vector<LoadItem*> arrLoadItem;
	typedef std::vector<LoadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem; //������ ���� ����
	int _currentGauge;		//���� �° �ε��ߴ��� ��Ÿ�� ������

public:
	void Init();			
	void Release();
	void Update();
	void Render();

	//���̹��� �ε�
	void LoadImg(std::string keyName, std::wstring fileName);
	//�������� �̹��� �ε�
	void LoadFrameImage(std::string keyName, std::wstring, int frameX, int frameY);
	//����� �ε� �Լ�
	void LoadSound(std::string keyName, const char* fileName, bool bgm = false, bool loop = false);

	BOOL LoadingDone(); //�ε��� �������� Ȯ���ϴ� �Լ�
	void LoadingWork();
	const arrLoadItem &GetLoadItem() { return _vLoadItem; }
	int GetCurrentGauge() { return _currentGauge; }
	wstring GetCurrentLoadName();

	Loading() = default;
	~Loading() = default;
};

