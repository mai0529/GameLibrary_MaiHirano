//-------------------------------------------
//
// ���ʗ񋓌^[common_malti.h]
// Author : ���앑
//
//-------------------------------------------
#ifndef _COMMON_H_		// ��d�C���N���[�h�h�~
#define _COMMON_H_

//-------------------------------------------
// 1P��2P��
//-------------------------------------------
enum MULTI_TYPE
{// 1P��2P��
	// �����Ȃ�
	MULTI_TYPE_NONE = 0,
	// 1P
	MULTI_TYPE_ONE,
	// 2P
	MULTI_TYPE_SECOND,
	// ���܂育�Ƃ̍ő吔
	COMMAND_TYPE_MAX
};

//-------------------------------------------
// �I�u�W�F�N�g���
//-------------------------------------------
enum OBJECT_TYPE
{
	// �����Ȃ�
	OBJECT_TYPE_NONE = 0,
	// �v���C���[
	OBJECT_TYPE_PLAYER,
	// ���C�t
	OBJECT_TYPE_LIFE,
	// �X�L��
	OBJECT_TYPE_SKILL,
	// �G
	OBJECT_TYPE_ENEMY,
	// �e
	OBJECT_TYPE_BULLET,
	// �A�C�e��
	OBJECT_TYPE_ITEM,
	// ��
	OBJECT_TYPE_WALL,
	// �G�t�F�N�g
	OBJECT_TYPE_EFFECT,
	// �p�[�e�B�N��
	OBJECT_TYPE_PARTICLE,
	// ���j���[
	OBJECT_TYPE_MENU,
	//��ނ̍ő吔
	OBJECT_TYPE_MAX
};

#endif		// _COMMON_H_