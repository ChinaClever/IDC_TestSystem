�}n =   �+��    ��j�b����O�;6��R�0��7;��{3�v�/�a��Ɲ�@؛w�"_��7�/R2].@�[-)�߼���mq�ɵ����	������% H�C1#]IX�{g��@z��sq�¢N.K�9��[ټ.L� 'Y��A2��jb����
��קBZ��D���@�!�a�m榐Vo5�K��3;�E|`������;�t@��n�y�B�
��!F�CW� ���F�/�Z��]փ�̾�eV9�l�7�j_���q���K�Hb��rғOi~�>p�sG���!߭��������)-
"禫D�9١.1Z?���nx	��'9*oy�S�Zfd^�����cq˚>���?��E1+��E�%�@q����k�`�e<��n�p0K�-��f��?[����R��W����i�+���g��E�$��΃)�d���7��_�,�����~����L�K3I
���N1�x���H�j��� = 0x03;
    mMsg->reg  = reg;
    mMsg->len  = len;

    return rtu_sent_packet(mMsg, buf);
}

int M_RtuSent::sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf)
{
    QMutexLocker locker(mMutex);

    mMsg->addr = addr;
    mMsg->fn   = 0x06;
    mMsg->reg  = reg;
    mMsg->len  = value;

    return rtu_sent_packet(mMsg, buf);
}
