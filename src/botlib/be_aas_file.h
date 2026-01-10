/*****************************************************************************
 * name:		be_aas_file.h
 *
 * desc:		AAS
 *
 *
 *****************************************************************************/

#ifdef AASINTERN
// loads the AAS file with the given name
int AAS_LoadAASFile(char *filename);
// writes an AAS file with the given name
qboolean AAS_WriteAASFile(char *filename);
// dumps the loaded AAS data
void AAS_DumpAASData(void);
// print AAS file information
void AAS_FileInfo(void);
#endif // AASINTERN
