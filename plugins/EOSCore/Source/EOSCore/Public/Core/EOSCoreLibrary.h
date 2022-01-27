/**
* Copyright (C) 2017-2020 | Dry Eel Development
*
* Official EOSCore Documentation: https://eeldev.com
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "eos_auth_types.h"
#include "eos_connect_types.h"
#include "Core/EOSTypes.h"
#include "Sessions/EOSSessionsTypes.h"
#include "Lobby/EOSLobbyTypes.h"
#include "EOSCoreLibrary.generated.h"

UENUM(BlueprintType)
enum class ELoginType : uint8
{
	/** Email / Password. Use of this login type is restricted. */
	Password = 0,
	/** Exchange code, typically generated by launcher */
	ExchangeCode = 1,
	/**
	 * Long-lived access token that is stored on the local device to allow persisting a user login session over multiple runs of the application.
	 * When using this login type, if an existing access token is not found or it is invalid or otherwise expired, the error result EOS_EResult::EOS_InvalidAuth is returned.
	 *
	 * @note On Desktop and Mobile platforms, the persistent access token is automatically managed by the SDK that stores it in the keychain of the currently logged in user of the local device.
	 * On Console platforms, after a successful login using the DeviceCode login type,
	 * the persistent access token is retrieved using the EOS_Auth_CopyUserAuthToken API and
	 * stored by the application for the currently logged in user of the local device.
	 */
	PersistentAuth = 2,
	/**
	 * Console platforms only; not available on Desktop or Mobile.
	 *
	 * Initiates a PIN grant login flow that is used to login a local user to their Epic Account for the first time,
	 * and also whenever their locally persisted login credentials would have expired.
	 *
	 * @details The flow is as following:
	 * 1. Game initiates the user login flow by calling EOS_Auth_Login API with the DeviceCode login type.
	 * 2. The SDK internally requests the authentication backend service to begin the login flow, and returns the game
	 * a new randomly generated device code along with authorization URL information needed to complete the flow.
	 * This information is returned via the EOS_Auth_Login API callback. The EOS_Auth_LoginCallbackInfo::ResultCode
	 * will be set to EOS_Auth_PinGrantCode and the EOS_Auth_PinGrantInfo struct will contain the needed information.
	 * 3. Game presents the device code and the authorization URL information on screen to the end-user.
	 * 4. The user will login to their Epic Account using an external device, e.g. a mobile device or a desktop PC,
	 * by browsing to the presented authentication URL and entering the device code presented by the game on the console.
	 * 5. Once the user has successfully logged in on their external device, the SDK will call the EOS_Auth_Login callback
	 * once more with the operation result code. If the user failed to login within the allowed time before the device code
	 * would expire, the result code returned by the callback will contain the appropriate error result.
	 *
	 * @details After logging in a local user for the first time, the game can remember the user login to allow automatically logging
	 * in the same user the next time they start the game. This avoids prompting the same user to go through the login flow
	 * across multiple game sessions over long periods of time.
	 * To do this, after a successful login using the DeviceCode login type, the game can call the EOS_Auth_CopyUserAuthToken API
	 * to retrieve a long-lived refresh token that is specifically created for this purpose on Console. The game can store
	 * the long-lived refresh token locally on the device, for the currently logged in local user of the device.
	 * Then, on subsequent game starts the game can call the EOS_Auth_Login API with the previously stored refresh token and
	 * using the PersistentAuth login type to automatically login the current local user of the device.
	 */
	DeviceCode = 3,
	/** Request credentials from the EOS SDK Dev Auth Tool */
	Developer = 4,
	/** Refresh token */
	RefreshToken = 5,
	/** Initiate a login through the account portal. Cannot be used on consoles. */
	AccountPortal = 6,
	/**
	 * Initiate a login through an external provider, such as Steam, PSN, XBL, or Nintendo.
	 *
	 * @details EOS_InvalidUser will be returned when the external auth login fails due to an external account not being linked.
	 * An EOS_ContinuanceToken will be set in the EOS_Auth_LoginCallbackInfo data.
	 * EOS_Auth_LinkAccount should be called with the EOS_ContinuanceToken to continue the external account login and link the external account.
	 */
	ExternalAuth = 7
};

UENUM(BlueprintType)
enum class ECredentialsType : uint8
{
	/**
	 * Epic Games User Token
	 *
	 * Acquired using EOS_Auth_CopyUserAuthToken that returns EOS_Auth_Token::AccessToken
	 */
	EPIC = 0,
	/**
	* Steam Encrypted App Ticket
	*
	* Generated using the ISteamUser::RequestEncryptedAppTicket API of Steamworks SDK.
	* For ticket generation parameters, use pDataToInclude(NULL) and cbDataToInclude(0).
	*
	* The retrieved App Ticket byte buffer needs to be converted into a hex-encoded UTF-8 string (e.g. "FA87097A..") before passing it to the EOS_Auth_Login or EOS_Connect_Login APIs.
	* For C/C++ API integration, use the EOS_ByteArray_ToString API for the conversion.
	* For C# integration, you can use <see cref="Helper.ToHexString" /> for the conversion.
	*/
	STEAM_APP_TICKET = 1,
	/**
	* Playstation ID Token
	*
	* Retrieved from the Playstation SDK. Please see first-party documentation for additional information.
	*/
	PSN_ID_TOKEN = 2,
	/**
	* Xbox Live User's XSTS Token
	*
	* Retrieved from the Xbox One XDK. Please see first-party documentation for additional information.
	*/
	XBL_XSTS_TOKEN = 3,
	/**
	* Discord Access Token
	*/
	DISCORD_ACCESS_TOKEN = 4,
	/**
	* GOG Galaxy Encrypted Session Ticket
	*/
	GOG_SESSION_TICKET = 5,
	/**
	* Nintendo Account ID Token
	*
	* This token identifies the user's Nintendo account and is acquired using web flow authentication.
	* On Nintendo Switch, the first time login requires the user to authenticate using their Nintendo account,
	* after which the login is automatic and uses the primary authentication method with NSA ID Token.
	*/
	NINTENDO_ID_TOKEN = 6,
	/**
	* Nintendo Service Account ID Token
	*
	* This is the device specific authentication token that is first used on login and will be linked with a Nintendo user account.
	*/
	NINTENDO_NSA_ID_TOKEN = 7,
	/**
	* Uplay Access Token
	*/
	UPLAY_ACCESS_TOKEN = 8,
	/**
	* OpenID Provider Access Token
	*/
	OPENID_ACCESS_TOKEN = 9,
	/**
	* Device ID access token that identifies the current locally logged in user profile on the local device.
	* The local user profile here refers to the operating system user login, for example the user's Windows Account
	* or on a mobile device the default active user profile.
	*
	* This credential type is used to automatically login the local user using the EOS Connect Device ID feature.
	*
	* The intended use of the Device ID feature is to allow automatically logging in the user on a mobile device
	* and to allow playing the game without requiring the user to necessarily login using a real user account at all.
	* This makes a seamless first-time experience possible and allows linking the local device with a real external
	* user account at a later time, sharing the same EOS_ProductUserId that is being used with the Device ID feature.
	*
	* @see EOS_Connect_CreateDeviceId
	*/
	DEVICEID_ACCESS_TOKEN = 10,
	/**
	* Apple Identity Token
	*/
	APPLE_ID_TOKEN = 11
};

UCLASS()
class EOSCORE_API UEOSCoreLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "EOSCore", meta = (WorldContext = "worldContextObject"))
		static bool EOS_Initialized(UObject* worldContextObject);

	UFUNCTION(BlueprintCallable, Category = "EOSCore")
		static bool UpdateUniqueNetIdFromOSS(APlayerController* playerController);

	/*
	* Attempt to login to the EOSCore Subsystem.
	* 
	* @return: if this function returns true it doesn't mean it logged in successfully but it was able to communicate with EOS
	*/
	UFUNCTION(BlueprintCallable, Category = "EOSCore", meta = (AutoCreateRefTerm = "data", WorldContext = "worldContextObject"))
		static bool Login(UObject* worldContextObject, APlayerController* playerController, FString loginId, FString password, ELoginType authType, ECredentialsType credentialsType, FString additionalData);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities")
		static FDateTime FromUnixTimestamp(FString timestamp);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities")
		static void BreakLobbyIdStruct(FEOSLobbyId id, FString& outId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities")
		static FEOSLobbyId MakeLobbyIdStruct(FString lobbyId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities")
		static void BreakAccessTokenStruct(FAccessToken token, FString& outToken);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities")
		static FAccessToken MakeAccessTokenStruct(FString token);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities")
		static void BreakLobbyInviteIdStruct(FLobbyInviteId inviteId, FString& outinviteId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities")
		static FLobbyInviteId MakeLobbyInviteIdStruct(FString inviteId);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities")
		static void BreakUIEventIdStruct(FEOSUIEventId eventId, FString& outEventId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities", meta = (DisplayName = "Is Valid"))
		static bool IsLobbyIdValid(FEOSLobbyId id);

	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities", meta = (ExpandEnumAsExecs = "result"))
		static void EOS_Success(EOSResult status, ESuccessFail& result);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities", meta = (CompactNodeTitle = "==", Keywords = "equal == identical"))
		static bool IsProductUserIdIdenticalWith(FEOSProductUserId a, FEOSProductUserId b);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities", meta = (CompactNodeTitle = "==", Keywords = "equal == identical"))
		static bool IsEpicAccountIdIdenticalWith(FEOSEpicAccountId a, FEOSEpicAccountId b);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities", meta = (CompactNodeTitle = "==", Keywords = "equal == identical"))
		static bool IsLobbyIdIdenticalWith(FEOSLobbyId a, FEOSLobbyId b);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Sessions|Utilities")
		static bool GetSessionAttributeBool(const FEOSSessionsAttributeData& data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Sessions|Utilities")
		static FString GetSessionAttributeInt64(const FEOSSessionsAttributeData& data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Sessions|Utilities")
		static FString GetSessionAttributeDouble(const FEOSSessionsAttributeData& data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Sessions|Utilities")
		static FString GetSessionAttributeString(const FEOSSessionsAttributeData& data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Lobby|Utilities")
		static bool GetLobbyAttributeBool(const FEOSLobbyAttributeData& data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Lobby|Utilities")
		static FString GetLobbyAttributeInt64(const FEOSLobbyAttributeData& data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Lobby|Utilities")
		static FString GetLobbyAttributeDouble(const FEOSLobbyAttributeData& data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Lobby|Utilities")
		static FString GetLobbyAttributeString(const FEOSLobbyAttributeData& data);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Sessions|Utilities")
		static FBucketId MakeBucketId(FString string);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Sessions|Utilities")
		static void BreakBucketId(FBucketId bucket, FString& string);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Sessions|Utilities")
		static FSessionInviteId MakeSessionsInviteId(FString string);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Sessions|Utilities")
		static void BreakSessionsInviteId(FSessionInviteId id, FString& string);

	/**
	* Returns a string representation of an EOS_EResult.
	* The return value is never null.
	* The return value must not be freed.
	*
	* Example: EOS_EResult_ToString(EOS_Success) returns "EOS_Success"
	*/
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static FString EOSEResultToString(EOSResult result);

	/**
	 * Returns whether a result is to be considered the final result, or false if the callback that returned this result
	 * will be called again either after some time or from another action.
	 *
	 * @param Result The result to check against being a final result for an operation
	 * @return True if this result means the operation is complete, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static bool EOSEResultIsOperationComplete(EOSResult result);

	/**
	 * Encode a byte array into hex encoded string
	 *
	 * @return An EOS_EResult that indicates whether the byte array was converted and copied into the OutBuffer.
	 *         EOS_Success if the encoding was successful and passed out in OutBuffer
	 *         EOS_InvalidParameters if you pass a null pointer on invalid length for any of the parameters
	 *         EOS_LimitExceeded - The OutBuffer is not large enough to receive the encoding. InOutBufferLength contains the required minimum length to perform the operation successfully.
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static EOSResult EOSByteArrayToString(const TArray<uint8> array, int32 length, FString& string);

	/**
	 * Check whether or not the given account unique id is considered valid
	 *
	 * @param AccountId The account id to check for validity
	 * @return EOS_TRUE if the EOS_EpicAccountId is valid, otherwise EOS_FALSE
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static bool EOSEpicAccountIdIsValid(FEOSEpicAccountId id);

	/**
	 * Check whether or not the given account unique id is considered valid
	 *
	 * @param AccountId The account id to check for validity
	 * @return EOS_TRUE if the EOS_EpicAccountId is valid, otherwise EOS_FALSE
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities", meta = (DisplayName = "EOSEpic Account Id is Valid (Pure)"))
		static bool EOSEpicAccountIdIsValidPure(FEOSEpicAccountId id) { return EOSEpicAccountIdIsValid(id); }

	/**
	 * Retrieve a string-ified account ID from an EOS_EpicAccountId. This is useful for replication of Epic account IDs in multiplayer games.
	 *
	 * @param AccountId The account ID for which to retrieve the string-ified version.
	 * @param OutBuffer The buffer into which the character data should be written
	 * @param InOutBufferLength The size of the OutBuffer in characters.
	 *                          The input buffer should include enough space to be null-terminated.
	 *                          When the function returns, this parameter will be filled with the length of the string copied into OutBuffer.
	 *
	 * @return An EOS_EResult that indicates whether the account ID string was copied into the OutBuffer.
	 *         EOS_Success - The OutBuffer was filled, and InOutBufferLength contains the number of characters copied into OutBuffer excluding the null terminator.
	 *         EOS_InvalidParameters - Either OutBuffer or InOutBufferLength were passed as NULL parameters.
	 *         EOS_InvalidUser - The AccountId is invalid and cannot be string-ified
	 *         EOS_LimitExceeded - The OutBuffer is not large enough to receive the account ID string. InOutBufferLength contains the required minimum length to perform the operation successfully.
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static EOSResult EOSEpicAccountIdToString(FEOSEpicAccountId id, FString& string);

	/**
	 * Retrieve an EOS_EpicAccountId from a raw account ID string. The input string must be null-terminated.
	 *
	 * @param AccountIdString The string-ified account ID for which to retrieve the EOS_EpicAccountId
	 * @return The EOS_EpicAccountId that corresponds to the AccountIdString
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static FEOSEpicAccountId EOSEpicAccountIdFromString(FString string);

	/**
	 * Check whether or not the given account unique id is considered valid
	 *
	 * @param AccountId The account id to check for validity
	 * @return EOS_TRUE if the EOS_ProductUserId is valid, otherwise EOS_FALSE
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static bool EOSProductUserIdIsValid(FEOSProductUserId id);

	/**
	 * Check whether or not the given account unique id is considered valid
	 *
	 * @param AccountId The account id to check for validity
	 * @return EOS_TRUE if the EOS_ProductUserId is valid, otherwise EOS_FALSE
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities", meta = (DisplayName = "EOSProduct User Id is Valid (Pure)"))
		static bool EOSProductUserIdIsValidPure(FEOSProductUserId id) { return EOSProductUserIdIsValid(id); }

	/**
	 * Retrieve a string-ified account ID from an EOS_ProductUserId. This is useful for replication of Product User IDs in multiplayer games.
	 *
	 * @param AccountId The account ID for which to retrieve the string-ified version.
	 * @param OutBuffer The buffer into which the character data should be written
	 * @param InOutBufferLength The size of the OutBuffer in characters.
	 *                          The input buffer should include enough space to be null-terminated.
	 *                          When the function returns, this parameter will be filled with the length of the string copied into OutBuffer.
	 *
	 * @return An EOS_EResult that indicates whether the account ID string was copied into the OutBuffer.
	 *         EOS_Success - The OutBuffer was filled, and InOutBufferLength contains the number of characters copied into OutBuffer excluding the null terminator.
	 *         EOS_InvalidParameters - Either OutBuffer or InOutBufferLength were passed as NULL parameters.
	 *         EOS_InvalidUser - The AccountId is invalid and cannot be string-ified
	 *         EOS_LimitExceeded - The OutBuffer is not large enough to receive the account ID string. InOutBufferLength contains the required minimum length to perform the operation successfully.
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static EOSResult EOSProductUserIdToString(FEOSProductUserId id, FString& string);

	/**
	 * Retrieve an EOS_EpicAccountId from a raw account ID string. The input string must be null-terminated.
	 *
	 * @param AccountIdString The string-ified account ID for which to retrieve the EOS_ProductUserId
	 * @return The EOS_ProductUserId that corresponds to the AccountIdString
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static FEOSProductUserId EOSProductUserIdFromString(FString string);

	/**
	 * Convert a string to a byte array, useful when sending chat messages
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static TArray<uint8> CoreStringToByte(FString string);
	
	/**
	 * Convert a byte array to a string, useful when receiving chat messages for example
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static FString CoreBytesToString(const TArray<uint8>& data);

	/*
	* Get the current product id of the last successful login
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities", meta = (WorldContext = "worldContextObject"))
		static FEOSProductUserId GetCurrentProductId(UObject* worldContextObject, int32 userIndex = 0);

	/*
	* Get the current account id of the last successful login
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EOSCore|Utilities", meta = (WorldContext = "worldContextObject"))
		static FEOSEpicAccountId GetCurrentAccountId(UObject* worldContextObject, int32 userIndex = 0);

	/**
	 * Retrieve a null-terminated string-ified continuance token from an EOS_ContinuanceToken.
	 *
	 * To get the required buffer size, call once with OutBuffer set to NULL, InOutBufferLength will contain the buffer size needed.
	 * Call again with valid params to get the string-ified continuance token which will only contain UTF8-encoded printable characters (excluding the null-terminator).
	 *
	 * @param ContinuanceToken The continuance token for which to retrieve the string-ified version.
	 * @param OutBuffer The buffer into which the character data should be written
	 * @param InOutBufferLength The size of the OutBuffer in characters.
	 *                          The input buffer should include enough space to be null-terminated.
	 *                          When the function returns, this parameter will be filled with the length of the string copied into OutBuffer including the null termination character.
	 *
	 * @return An EOS_EResult that indicates whether the Epic Online Services Account ID string was copied into the OutBuffer.
	 *         EOS_Success - The OutBuffer was filled, and InOutBufferLength contains the number of characters copied into OutBuffer including the null terminator.
	 *         EOS_InvalidParameters - Either OutBuffer or InOutBufferLength were passed as NULL parameters.
	 *         EOS_InvalidUser - The AccountId is invalid and cannot be string-ified
	 *         EOS_LimitExceeded - The OutBuffer is not large enough to receive the continuance token string. InOutBufferLength contains the required minimum length to perform the operation successfully.
	 */
	UFUNCTION(BlueprintCallable, Category = "EOSCore|Utilities")
		static EOSResult EOSContinuanceTokenToString(FContinuanceToken id, FString& string);


};
