import hmbind
import nmath
import random


def main():
    nameList = ["Funkyplant_small", "Fern_big", "Pine_01", "Stump_01", "Unit_Catapult", "Unit_Footman"]
    itemList = ["mdl:Vegetation/Funkyplant_small.n3", "mdl:Vegetation/Fern_big.n3",
                "mdl:Vegetation/Pine_01.n3", "mdl:Vegetation/Stump_01.n3", "mdl:Units/Unit_Catapult.n3",
                "mdl:Units/Unit_Footman.n3"]

    em = hmbind.EntityManager()
    em.createEntity("ground", "mdl:environment/Groundplane.n3", "NONE")
    em.createPointLight("light", nmath.Float4(1.0, 1.0, 1.0, 1.0), 10.0, nmath.Point(1.0, 3.5, 1.0), 100.0, True)

    for n in range(0, 10):
        r = random.randint(0, 5)
        x = random.random() * 20.0 - 10.0
        z = random.random() * 20.0 - 10.0
        name = str.format("{0}_{1}", nameList[r], n)
        em.createEntity(name, itemList[r], "NONE", nmath.Point(x, 0.1, z))

    # catapult = em.createEntity("catapult", "mdl:Units/Unit_Catapult.n3", "NONE")
    # catapultMotion = catapult.createMotionComponent()
    # catapultMotion.setAngularVelocity(nmath.Float4(0.0, 1.2, 0.0, 0.0));
    #
    # placeholder = em.createEntity("fern", "mdl:Vegetation/Fern_big.n3", "NONE", nmath.Point(0.0, 0.0, 0.0))
    # phMotion = placeholder.createMotionComponent()
    # phMotion.setVelocity(nmath.Float4(1.0, 0.0, 0.0, 0.0))
    # phMotion.setAngularVelocity(nmath.Float4(0.0, 2.0, 0.0, 0.0))
    #
    # character = em.createCharacter("footman", "mdl:Units/Unit_Footman.n3", "ske:Units/Unit_Footman.nsk3", "ani:Units/Unit_Footman.nax3", "NONE", nmath.Point(2.0, 0.0, -20.0))
    # characterComp = character.getCharacterComponent()
    # characterComp.playAnimation(0, 0, hmbind.CharacterComponent.EnqueueMode.APPEND, 1.0, 1, random.random() * 100.0, 0.0, 0.0, random.random() * 100.0)
    # characterMotion = character.createMotionComponent()
    # characterMotion.setVelocity(nmath.Float4(0.0, 0.0, 4.0, 0.0))


if __name__ == '__main__':
    main()