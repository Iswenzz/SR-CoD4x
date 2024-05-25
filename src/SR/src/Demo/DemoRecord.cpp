#include "DemoRecord.hpp"

namespace Iswenzz::CoD4x
{
	void DemoRecord::WriteSnapshot(client_t *client, msg_t *msg)
	{
		snapshotInfo_t snapInfo;
		int lastframe;
		int from_num_entities;
		int newindex, oldindex, newnum, oldnum;
		clientState_t *newcs, *oldcs;
		entityState_t *newent, *oldent;
		clientSnapshot_t *frame, *oldframe;
		int i;
		int snapFlags;
		int var_x, from_first_entity, from_num_clients, from_first_client;

		snapInfo.clnum = client - svsHeader.clients;
		snapInfo.client = (void *)client;
		snapInfo.snapshotDeltaTime = 0;
		snapInfo.fromBaseline = 0;
		snapInfo.archived = 0;

		frame = &client->frames[client->netchan.outgoingSequence & PACKET_MASK];
		frame->var_03 = svsHeader.time;

		if (client->deltaMessage <= 0 || client->state != CS_ACTIVE)
		{
			oldframe = NULL;
			lastframe = 0;
			var_x = 0;
		}
		else if (client->demorecording && !client->demoDeltaFrameCount)
		{
			Com_DPrintf(CON_CHANNEL_SERVER, "Force a nondelta frame for %s for demo recording\n", client->name);

			oldframe = NULL;
			lastframe = 0;
			var_x = 0;
			client->demowaiting = qfalse;
		}
		else
		{
			int deltaMessage = client->netchan.outgoingSequence - 1;
			oldframe = &client->frames[deltaMessage & PACKET_MASK];
			lastframe = 1;
			var_x = oldframe->var_03;
		}
		MSG_WriteByte(msg, svc_snapshot);
		MSG_WriteLong(msg, svsHeader.time);
		MSG_WriteByte(msg, lastframe);
		snapInfo.snapshotDeltaTime = var_x;
		snapFlags = svsHeader.snapFlagServerBit;

		if (client->rateDelayed)
			snapFlags |= 1;

		if (client->state == CS_ACTIVE)
			client->unksnapshotvar = 1;
		else if (client->state != CS_ZOMBIE)
			client->unksnapshotvar = 0;

		if (!client->unksnapshotvar)
			snapFlags |= 2;
		MSG_WriteByte(msg, snapFlags);

		if (oldframe)
		{
			MSG_WriteDeltaPlayerstate(&snapInfo, msg, svsHeader.time, &oldframe->ps, &frame->ps);
			from_num_entities = oldframe->num_entities;
			from_first_entity = oldframe->first_entity;
			from_num_clients = oldframe->num_clients;
			from_first_client = oldframe->first_client;
		}
		else
		{
			MSG_WriteDeltaPlayerstate(&snapInfo, msg, svsHeader.time, 0, &frame->ps);
			from_num_entities = 0;
			from_first_entity = 0;
			from_num_clients = 0;
			from_first_client = 0;
		}
		MSG_ClearLastReferencedEntity(msg);

		newindex = 0;
		oldindex = 0;

		while (newindex < frame->num_entities || oldindex < from_num_entities)
		{
			if (newindex >= frame->num_entities)
			{
				newnum = 9999;
				newent = NULL;
			}
			else
			{
				newent = &svsHeader.snapshotEntities[(frame->first_entity + newindex) % svsHeader.numSnapshotEntities];
				newnum = newent->number;
			}

			if (oldindex >= from_num_entities)
			{
				oldnum = 9999;
				oldent = NULL;
			}
			else
			{
				oldent = &svsHeader.snapshotEntities[(from_first_entity + oldindex) % svsHeader.numSnapshotEntities];
				oldnum = oldent->number;
			}

			if (newnum == oldnum)
			{
				// Delta update from old position
				// Because the force parm is qfalse, this will not result
				// In any bytes being emited if the entity has not changed at all
				MSG_WriteDeltaEntity(&snapInfo, msg, svsHeader.time, oldent, newent, qfalse);
				oldindex++;
				newindex++;
				continue;
			}
			if (newnum < oldnum)
			{
				// This is a new entity, send it from the baseline
				snapInfo.fromBaseline = 1;
				MSG_WriteDeltaEntity(&snapInfo, msg, svsHeader.time, &svsHeader.svEntities[newnum].baseline.s, newent,
					qtrue);
				snapInfo.fromBaseline = 0;
				newindex++;
				continue;
			}
			if (newnum > oldnum)
			{
				// The old entity isn't present in the new message
				MSG_WriteDeltaEntity(&snapInfo, msg, svsHeader.time, oldent, NULL, qtrue);
				oldindex++;
				continue;
			}
		}
		MSG_WriteEntityIndex(&snapInfo, msg, (MAX_GENTITIES - 1), GENTITYNUM_BITS);
		MSG_ClearLastReferencedEntity(msg);

		newindex = 0;
		oldindex = 0;

		while (newindex < frame->num_clients || oldindex < from_num_clients)
		{
			if (newindex >= frame->num_clients)
			{
				newnum = 9999;
				newcs = NULL;
			}
			else
			{
				newcs = &svsHeader.snapshotClients[(frame->first_client + newindex) % svsHeader.numSnapshotClients];
				newnum = newcs->clientIndex;
			}

			if (oldindex >= from_num_clients)
			{
				oldnum = 9999;
				oldcs = NULL;
			}
			else
			{
				oldcs = &svsHeader.snapshotClients[(from_first_client + oldindex) % svsHeader.numSnapshotClients];
				oldnum = oldcs->clientIndex;
			}

			if (newnum == oldnum)
			{
				// Delta update from old position
				// Because the force parm is qfalse, this will not result
				// In any bytes being emited if the entity has not changed at all
				MSG_WriteDeltaClient(&snapInfo, msg, svsHeader.time, oldcs, newcs, qfalse);
				oldindex++;
				newindex++;
				continue;
			}
			if (newnum < oldnum)
			{
				MSG_WriteDeltaClient(&snapInfo, msg, svsHeader.time, NULL, newcs, qtrue);
				newindex++;
				continue;
			}
			if (newnum > oldnum)
			{
				MSG_WriteDeltaClient(&snapInfo, msg, svsHeader.time, oldcs, NULL, qtrue);
				oldindex++;
				continue;
			}
		}
		MSG_WriteBit0(msg);

		if (sv_padPackets->integer)
		{
			for (i = 0; i < sv_padPackets->integer; i++)
				MSG_WriteByte(msg, 0); // svc_nop
		}
	}

	void DemoRecord::BeginSnapshot(client_t *client, msg_t *msg)
	{
		static byte tempDemoSnapshotMsgBuf[NETCHAN_UNSENTBUFFER_SIZE];

		MSG_Init(msg, tempDemoSnapshotMsgBuf, sizeof(tempDemoSnapshotMsgBuf));
		MSG_ClearLastReferencedEntity(msg);
		MSG_WriteLong(msg, client->lastClientCommand);

		if (client->state >= CS_CONNECTED || client->state == CS_ZOMBIE)
			SV_UpdateServerCommandsToClient(client, msg);
		if (client->state >= CS_CONNECTED && client->gamestateSent)
			SV_UpdateConfigData(client, msg);
	}

	void DemoRecord::EndSnapshot(client_t *client, msg_t *msg)
	{
		byte svCompressBuf[4 * 65536];

		MSG_WriteByte(msg, svc_EOF);

		int len;
		*(int32_t *)svCompressBuf = *(int32_t *)msg->data;
		len = MSG_WriteBitsCompress(msg->data + 4, (byte *)svCompressBuf + 4, msg->cursize - 4);
		len += 4;

		if (client->demorecording && !client->demowaiting && client->demofile.handleFiles.file.o)
			SV_WriteDemoMessageForClient(svCompressBuf, len, client);
	}

	void DemoRecord::Frame(client_t *cl)
	{
		if (!cl->demorecording)
			return;

		msg_t demoMsg;

		BeginSnapshot(cl, &demoMsg);
		if (cl->state == CS_ACTIVE || cl->state == CS_ZOMBIE)
			WriteSnapshot(cl, &demoMsg);
		EndSnapshot(cl, &demoMsg);

		cl->demoDeltaFrameCount = 1;
	}
}
